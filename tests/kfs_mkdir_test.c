#include <check.h>

#include <kfs_mkdir.h

#include "test_main.h"

void kfs_mkdir_setup(void) {
    main_setup();
}

void kfs_mkdir_teardown(void) {

}

START_TEST(kfs_mkdir_base) {
    kfs_mkdir()
}
END_TEST

Suite * kfs_mkdir_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("kfs_mkdir()");
    tc_core = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tc_core, kfs_mkdir_setup, kfs_mkdir_teardown);
    tcase_add_test(tc_core, kfs_mkdir_base);
    suite_add_tcase(s, tc_core);

    return s;
}
