
#include <check.h>

int i;

void kfs_read_setup(void) {
    i = 10;
}

void kfs_read_teardown(void) {
}

START_TEST(kfs_read_base) {
   // empty test here
}
END_TEST

Suite * kfs_read_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("kfs_read()");
    tc_core = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tc_core, kfs_read_setup, kfs_read_teardown);
    tcase_add_test(tc_core, kfs_read_base);

    suite_add_tcase(s, tc_core);

    return s;
}
