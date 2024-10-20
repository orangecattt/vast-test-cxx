enable_testing()

configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

SET(TESTCASE "." CACHE STRING "testcases to run, list of files or directories, relative path to 'testcases' directory")

add_test(
    NAME vast-test-cxx
    COMMAND lit -v ${TESTCASE}
)

unset(TESTCASE CACHE)
