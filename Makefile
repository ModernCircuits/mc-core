BUILD_DIR ?= cmake-build-debug

CLANG_FORMAT_BINARY ?= clang-format
CLANG_TIDY_BINARY ?= clang-tidy-13
CLANG_APPLY_BINARY ?= clang-apply-replacements-13

CLANG_TIDY_ARGS += -clang-tidy-binary ${CLANG_TIDY_BINARY}
CLANG_TIDY_ARGS += -clang-apply-replacements-binary ${CLANG_APPLY_BINARY}
CLANG_TIDY_ARGS += -j $(shell nproc)
CLANG_TIDY_ARGS += -quiet
CLANG_TIDY_ARGS += -p $(BUILD_DIR)

.PHONY: tidy-check
tidy-check:
	 ./scripts/run-clang-tidy.py $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./mc) $(shell realpath ./)

.PHONY: tidy-fix
tidy-fix:
	 ./scripts/run-clang-tidy.py -fix $(CLANG_TIDY_ARGS) -header-filter $(shell realpath ./mc) $(shell realpath ./)

.PHONY: coverage
coverage:
	cmake -S. -GNinja -Bcmake-build-coverage -DCMAKE_BUILD_TYPE=Debug -DMC_BUILD_COVERAGE=TRUE
	cmake --build cmake-build-coverage
	cd cmake-build-coverage && ctest

.PHONY: coverage-html
coverage-html: coverage
	cd cmake-build-coverage && gcovr --html --html-details --exclude-unreachable-branches -o coverage.html -r ../mc -j ${shell nproc} -s .

.PHONY: coverage-xml
coverage-xml: coverage
	cd cmake-build-coverage && gcovr --xml-pretty --exclude-unreachable-branches -o coverage.xml  -r ../mc -j ${shell nproc} -s .


.PHONY: report
report:
	cd cmake-build-coverage && genhtml cov.info --output-directory lcov

.PHONY: stats
stats:
	@cloc -by-file-by-lang --exclude-dir=3rd_party --exclude-ext=svg --vcs=git .

.PHONY: format
format:
	@find mc -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BINARY} -i
	@find tests -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs ${CLANG_FORMAT_BINARY} -i

.PHONY: format-check
format-check:
	@find mc -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BINARY} -style=file {} | diff - {}'
	@find tests -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c '${CLANG_FORMAT_BINARY} -style=file {} | diff - {}'
