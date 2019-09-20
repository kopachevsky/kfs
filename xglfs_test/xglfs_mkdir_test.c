#include <check.h>
#include <xglfs_mkdir.h>

#include "xglfs_test_main.h"

void xglfs_mkdir_setup(void) {
    main_setup();
}

void xglfs_mkdir_teardown(void) {
    main_teardown();
}

START_TEST(xglfs_mkdir_creation) {
    int res = xglfs_mkdir("dir",0777);
    ck_assert_int_eq(res,0);
}
END_TEST

Suite *xglfs_mkdir_suite(void) {
    Suite *suite = suite_create("xglfs_mkdir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, xglfs_mkdir_setup, xglfs_mkdir_teardown);
    tcase_add_test(tcase, xglfs_mkdir_creation);
    suite_add_tcase(suite, tcase);
    return suite;
}

