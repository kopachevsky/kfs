#include <check.h>
#include <kfs_open.h>
#include <fcntl.h>

#include "test_main.h"

void kfs_open_setup(void) {
    main_setup();
}

void kfs_open_teardown(void) {
    main_teardown();
}

START_TEST(kfs_open_exist) {
    int res = creat("exist.txt", 0777);
    ck_assert_int_ne(res, 0);
    char *path = str_concat(LOCAL_DISC_CACHE_PATH, "exist.txt");
    FILE *file = kfs_open(path, O_RDWR);
    fail_if(file == NULL);
}
END_TEST

START_TEST(kfs_open_not_exist) {
    FILE *file = kfs_open("not_exist.txt", O_RDONLY);
    ck_assert_int_eq(file, -ENOENT);
}
END_TEST

START_TEST(kfs_open_chmod) {
    int res = creat("chmod.txt", O_RDONLY);
    ck_assert_int_ne(res,0);
    char *path = str_concat(LOCAL_DISC_CACHE_PATH, "chmode.txt");
    FILE *file = kfs_open(path, O_WRONLY);
    ck_assert_int_ne(file, -EACCES);
}
END_TEST

START_TEST(kfs_open_read) {
    int res = creat("read.txt", O_RDONLY);
    ck_assert_int_ne(res,0);
    char *path = str_concat(LOCAL_DISC_CACHE_PATH, "read.txt");
    FILE *write = kfs_open(path, O_WRONLY);
    ck_assert_int_eq(write, -ENOENT);
    FILE *read = kfs_open(path, O_RDONLY);
    fail_if(read == NULL);
}
END_TEST

START_TEST(kfs_open_write) {
    int res = creat("write.txt", O_WRONLY);
    ck_assert_int_ne(res, 0);
    char *path = str_concat(LOCAL_DISC_CACHE_PATH, "write.txt");
    FILE *read = kfs_open(path, O_RDONLY);
    ck_assert_int_eq(read, -ENOENT);
    FILE *write = kfs_open(path, O_WRONLY);
    fail_if(write == NULL);
}
END_TEST

Suite * kfs_open_suite(void) {
    Suite *suite = suite_create("kfs_open()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_open_setup, kfs_open_teardown);
    tcase_add_test(tcase, kfs_open_exist);
    tcase_add_test(tcase, kfs_open_not_exist);
    tcase_add_test(tcase, kfs_open_chmod);
    tcase_add_test(tcase, kfs_open_read);
    tcase_add_test(tcase, kfs_open_write);
    suite_add_tcase(suite, tcase);
    return suite;
}
