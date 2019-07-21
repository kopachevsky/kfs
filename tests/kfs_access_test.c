#include <check.h>

int i;

void kfs_acces_setup(void) {
    i = 10;
}

void kfs_acces_teardown(void) {

}

START_TEST(kfs_access_base) {
   // empty test here
}
END_TEST

Suite * kfs_access_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("kfs_access()");
    tc_core = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tc_core, kfs_acces_setup, kfs_acces_teardown);
    tcase_add_test(tc_core, kfs_access_base);

    suite_add_tcase(s, tc_core);

    return s;
}
