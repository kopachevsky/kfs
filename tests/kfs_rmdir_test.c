#include <check.h>
#include <kfs_rmdir.h>
#include <kfs_mkdir.h>
#include <dirent.h>

#include "test_main.h"

void kfs_rmdir_setup(void) {
    main_setup();
}

void kfs_rmdir_teardown(void) {
    main_teardown();
}

START_TEST(kfs_rmdir_base) {
    int res = kfs_mkdir("rmdir_base/", 0777);
    ck_assert_int_eq(res, 0);
    res = kfs_rmdir("rmdir_base/");
    ck_assert_int_eq(res, 0);
    DIR* dir = opendir("rmdir_base/");
    fail_if(dir != NULL);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH, "rmdir_base/" ));

}
END_TEST


START_TEST(kfs_rmdir_not_existing_folder) {
    int res = kfs_rmdir("rmdir_not_existing_folder/");
    ck_assert_int_eq(res, -ENOENT);
    DIR* dir = opendir("rmdir_not_existing_folder/");
    fail_if(dir != NULL);
}
END_TEST

Suite *kfs_rmdir_suite(void) {
    Suite *suite = suite_create("kfs_rmdir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_rmdir_setup, kfs_rmdir_teardown);
    tcase_add_test(tcase, kfs_rmdir_base);
    tcase_add_test(tcase, kfs_rmdir_not_existing_folder);
    suite_add_tcase(suite, tcase);
    return suite;
}
