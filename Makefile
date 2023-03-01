CXX_STD ?= 17

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
	${CLANG_TIDY_ARGS} -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./src) $(shell realpath ./src)

.PHONY: tidy-fix
tidy-fix:
	${CLANG_TIDY_ARGS} -fix -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./src) $(shell realpath ./src)

.PHONY: check
check:
	pre-commit run --all-files

.PHONY: coverage
coverage:
	conan install -of cmake-build-coverage --build=missing -pr=default -c tools.cmake.cmaketoolchain:generator=Ninja -s compiler.cppstd=${CXX_STD} -s build_type=Debug .
	cmake -S . -B=cmake-build-coverage -DCMAKE_TOOLCHAIN_FILE="cmake-build-coverage/conan_toolchain.cmake" -GNinja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_STANDARD="${CXX_STD}" -DMODERNCIRCUITS_ENABLE_COVERAGE=TRUE
	cmake --build cmake-build-coverage
	ctest --test-dir cmake-build-coverage -C Debug --output-on-failure

.PHONY: coverage-html
coverage-html: coverage
	gcovr --html --html-details -e ".*test\.cpp" --exclude-unreachable-branches -r src -j ${shell nproc} -s cmake-build-coverage -o cmake-build-coverage/coverage.html

.PHONY: coverage-xml
coverage-xml: coverage
	gcovr --xml-pretty -e ".*test\.cpp" --exclude-unreachable-branches -r src -j ${shell nproc} -s cmake-build-coverage -o cmake-build-coverage/coverage.xml


.PHONY: report
report:
	cd cmake-build-coverage && genhtml cov.info --output-directory lcov

.PHONY: stats
stats:
	@cloc -by-file-by-lang --exclude-dir=3rd_party --exclude-ext=svg --vcs=git .

.PHONY: format
format:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BIN} -i

.PHONY: format-check
format-check:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BIN} -style=file {} | diff - {}'

.PHONY: format-rst
format-rst:
	@find docs -iname '*.rst' -o -iname '*.rstinc' | xargs docstrfmt

.PHONY: format-rst-check
format-rst-check:
	@find docs -iname '*.rst' -o -iname '*.rstinc' | xargs docstrfmt -c
