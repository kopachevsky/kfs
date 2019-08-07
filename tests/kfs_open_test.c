#include <check.h>
#include <kfs_open.h>
#include <kfs_create.h>

#include "test_main.h"

void kfs_open_setup(void) {
    main_setup();
}

void kfs_open_teardown(void) {
    main_teardown();
}

START_TEST(kfs_open_exist) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = {O_RDONLY|O_WRONLY};
    res = kfs_open(path, &open);
    fail_if(open.fh == 0);
    fail_if(res != 0);
    fail_if(path == NULL);
}
END_TEST

START_TEST(kfs_open_not_exist) {
    struct fuse_file_info open = {O_RDONLY|O_WRONLY};
    int res = kfs_open("not_exist.txt", &open);
    ck_assert_int_eq(res, -ENOENT);
}
END_TEST

START_TEST(kfs_open_chmod) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("chmod.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "chmod.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0111, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = {O_RDWR};
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, -EACCES);
    fail_if(path == NULL);
}
END_TEST

START_TEST(kfs_open_read) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("read.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "read.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0444, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open_write = {O_WRONLY};
    res = kfs_open(path, &open_write);
    ck_assert_int_eq(res, -EACCES);
    struct fuse_file_info open_read = {O_RDONLY};
    res = kfs_open(path, &open_read);
    ck_assert_int_eq(res, 0);
    fail_if(path == NULL);
}
END_TEST

START_TEST(kfs_open_write) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("write.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "write.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0222, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open_read = {O_RDONLY};
    res = kfs_open(path, &open_read);
    ck_assert_int_eq(res, -EACCES);
    struct fuse_file_info open_write = {O_WRONLY};
    res = kfs_open(path, &open_write);
    ck_assert_int_eq(res, 0);
    fail_if(path == NULL);
}
END_TEST

Suite *kfs_open_suite(void) {
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
