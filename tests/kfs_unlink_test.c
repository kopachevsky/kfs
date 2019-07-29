#include <check.h>
#include <kfs_link.h>
#include <kfs_unlink.h>
#include <fcntl.h>

#include "test_main.h"

void kfs_unlink_setup(void) {
    main_setup();
}

void kfs_unlink_teardown(void) {
    main_teardown();
}

START_TEST(kfs_unlink_exist_files) {
    int res = creat("file1.txt", 0777);
    ck_assert_int_ne(res, 0);
    int ves = creat("/tmp/file2.txt", 0777);
    ck_assert_int_ne(ves, 0);
    char *path1 = str_concat(LOCAL_DISC_CACHE_PATH, "file.txt");
    char *path2 = "/tmp/file2.txt";
    FILE *link = kfs_link(path1, path2);
    fail_if(link == NULL);
    FILE *unlink = kfs_unlink(path2);
    fail_unless(unlink == NULL);
}
END_TEST

START_TEST(kfs_unlink_not_exist_files) {
    int res = creat("file1.txt", 0777);
    ck_assert_int_ne(res, 0);
    char *path1 = str_concat(LOCAL_DISC_CACHE_PATH, "file1.txt");
    int ves = creat("file2.txt", 0777);
    ck_assert_int_ne(ves, 0);
    char *path2 = str_concat(LOCAL_DISC_CACHE_PATH, "file2.txt");
    FILE *link = kfs_link(path1, path2);
    fail_if(link == NULL);
    char *link_path = str_concat(path1,path2);
    FILE *unlink = kfs_unlink(link_path);
    ck_assert_int_eq(unlink, -ENOENT);
}
END_TEST

Suite * kfs_unlink_suite(void) {
    Suite *suite = suite_create("kfs_unlink()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_unlink_setup, kfs_unlink_teardown);
    tcase_add_test(tcase, kfs_unlink_exist_files);
    tcase_add_test(tcase, kfs_unlink_not_exist_files);
    suite_add_tcase(suite, tcase);
    return suite;
}


