BUILD_DIR ?= cmake-build-debug

CLANG_FORMAT_BIN ?= clang-format
CLANG_TIDY_BIN ?= clang-tidy-14
CLANG_APPLY_BIN ?= clang-apply-replacements-14

CLANG_TIDY_ARGS += -clang-tidy-binary ${CLANG_TIDY_BIN}
CLANG_TIDY_ARGS += -clang-apply-replacements-binary ${CLANG_APPLY_BIN}
CLANG_TIDY_ARGS += -j $(shell nproc)
CLANG_TIDY_ARGS += -quiet
CLANG_TIDY_ARGS += -p $(BUILD_DIR)

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./src) $(shell realpath ./)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -fix $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./src) $(shell realpath ./)

.PHONY: coverage
coverage:
	conan install -if "cmake-build-coverage" --build=missing -pr:b=default -pr:h=default -s compiler.cppstd=14 -s build_type=Debug .
	cd "cmake-build-coverage" && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DMC_CORE_ENABLE_COVERAGE=TRUE
	cmake --build "cmake-build-coverage"
	cd "cmake-build-coverage" && ctest

.PHONY: coverage-html
coverage-html: coverage
	cd cmake-build-coverage && gcovr --html --html-details --exclude-unreachable-branches -o coverage.html -r ../src -j ${shell nproc} -s .

.PHONY: coverage-xml
coverage-xml: coverage
	cd cmake-build-coverage && gcovr --xml-pretty --exclude-unreachable-branches -o coverage.xml  -r ../src -j ${shell nproc} -s .


.PHONY: report
report:
	cd cmake-build-coverage && genhtml cov.info --output-directory lcov

.PHONY: stats
stats:
	@cloc -by-file-by-lang --exclude-dir=3rd_party --exclude-ext=svg --vcs=git .

.PHONY: format
format:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BIN} -i
	@find tests -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BIN} -i

.PHONY: format-check
format-check:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BIN} -style=file {} | diff - {}'
	@find tests -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BIN} -style=file {} | diff - {}'
