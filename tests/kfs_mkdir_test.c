#include <check.h>
#include <kfs_mkdir.h>
#include <dirent.h>

#include "test_main.h"



void kfs_mkdir_setup(void) {
    main_setup();
    ck_assert_int_eq(21, strlen(LOCAL_DISC_CACHE_PATH));
}

void kfs_mkdir_teardown(void) {
    main_teardown();
}

START_TEST(kfs_mkdir_creation) {
    int res = kfs_mkdir("mydir", 0777);
    fail_unless(res == 0);
    ck_assert_int_ne("mydir", 0);
}
END_TEST

START_TEST(kfs_mkdir_exist) {
    int dir1 = kfs_mkdir("test", 0777);
    ck_assert_int_eq(dir1, 0);
    int dir2 = kfs_mkdir("test", 0777);
    ck_assert_int_ne(dir2, 0);
    fail_unless("test" != 0);
}
END_TEST

Suite * kfs_mkdir_suite(void) {
    Suite *suite = suite_create("kfs_mkdir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_mkdir_setup, kfs_mkdir_teardown);
    tcase_add_test(tcase, kfs_mkdir_creation);
    tcase_add_test(tcase, kfs_mkdir_exist);
    suite_add_tcase(suite, tcase);
    return suite;
}
