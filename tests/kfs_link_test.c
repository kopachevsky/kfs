#include <check.h>
#include <kfs_link.h>
#include <fcntl.h>

#include "test_main.h"

void kfs_link_setup(void) {
    main_setup();
}

void kfs_link_teardown(void) {
    main_teardown();
}

START_TEST(kfs_link_exist_files) {
    int res = creat("file1.txt", 0777);
    ck_assert_int_ne(res, 0);
    char *path1 = str_concat(LOCAL_DISC_CACHE_PATH, "file1.txt");
    int ves = creat("file2.txt", 0777);
    ck_assert_int_ne(ves, 0);
    char *path2 = str_concat(LOCAL_DISC_CACHE_PATH, "file2.txt");
    FILE *file = kfs_link(path1, path2);
    fail_if(file == NULL);
}
END_TEST

START_TEST(kfs_link_not_exist_files) {
    int res = creat("file1.txt", 0777);
    ck_assert_int_ne(res, 0);
    char *path1 = str_concat(LOCAL_DISC_CACHE_PATH, "file1.txt");
    res = unlink(path1);
    ck_assert_int_ne(res,0);
    int ves = creat("file2.txt", 0777);
    ck_assert_int_ne(ves, 0);
    char *path2 = str_concat(LOCAL_DISC_CACHE_PATH, "file2.txt");
    ves = unlink(path2);
    ck_assert_int_ne(ves, 0);
    FILE *file = kfs_link(path1, path2);
    ck_assert_int_eq(file, -ENOENT);
}
END_TEST

Suite * kfs_link_suite(void) {
    Suite *suite = suite_create("kfs_link()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_link_setup, kfs_link_teardown);
    tcase_add_test(tcase, kfs_link_exist_files);
    tcase_add_test(tcase, kfs_link_not_exist_files);
    suite_add_tcase(suite, tcase);
    return suite;
}


