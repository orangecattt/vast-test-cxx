cmake_minimum_required(VERSION 3.12)

enable_testing()

configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

SET(VAST_PATH "" CACHE STRING "path to vast")
SET(LIT_PATH "" CACHE STRING "path to lit")
SET(TESTCASE "." CACHE STRING "testcases to run, list of files or directories, relative path to 'testcases' directory")

string(JOIN "/" LIT ${LIT_PATH} ${LIT_BIN_NAME})

add_test(
    NAME vast-test-cxx
    COMMAND ${LIT} -v ${TESTCASE}
)

unset(TESTCASE CACHE)
unset(VAST_PATH CACHE)
unset(LIT_PATH CACHE)
