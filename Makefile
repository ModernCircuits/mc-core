CXX_STD ?= 14

BUILD_DIR ?= cmake-build-debug

BUILD_DIR ?= build
PYTHON_BIN ?= python3
CLANG_FORMAT_BIN ?= clang-format
CLANG_REPLACEMENTS_BIN ?= clang-apply-replacements
CLANG_TIDY_BIN ?= clang-tidy
RUN_CLANGTIDY_BIN ?= $(shell which run-clang-tidy)

CLANG_TIDY_ARGS =  ${PYTHON_BIN}
CLANG_TIDY_ARGS += ${RUN_CLANGTIDY_BIN}
CLANG_TIDY_ARGS += -clang-tidy-binary
CLANG_TIDY_ARGS += ${CLANG_TIDY_BIN}
CLANG_TIDY_ARGS += -clang-apply-replacements-binary
CLANG_TIDY_ARGS += ${CLANG_REPLACEMENTS_BIN}
CLANG_TIDY_ARGS += -j $(shell nproc)

.PHONY: tidy-check
tidy-check:
	${CLANG_TIDY_ARGS} -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./src) $(shell realpath ./tests)

.PHONY: tidy-fix
tidy-fix:
	${CLANG_TIDY_ARGS} -fix -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./src) $(shell realpath ./tests)

.PHONY: check
check:
	pre-commit run --all-files

.PHONY: coverage
coverage:
	conan install -if "cmake-build-coverage" --build=missing -pr:b=default -pr:h=default -e mc-core:CONAN_RUN_TESTS=True -s compiler.cppstd=${CXX_STD} -s build_type=Debug .
	cd "cmake-build-coverage" && cmake .. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD="${CXX_STD}" -DMC_CORE_ENABLE_COVERAGE=TRUE
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

.PHONY: format-rst
format-rst:
	@find docs -iname '*.rst' -o -iname '*.rstinc' | xargs docstrfmt

.PHONY: format-rst-check
format-rst-check:
	@find docs -iname '*.rst' -o -iname '*.rstinc' | xargs docstrfmt -c
