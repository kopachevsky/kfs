#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_write.h>
#include <kfs_read.h>
#include <stdio.h>

#include "test_main.h"

void kfs_read_setup(void) {
    main_setup();
}

void kfs_read_teardown(void) {
    main_teardown();
}

START_TEST(kfs_read_exist_file_with_content) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist_content.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist_content.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    res = kfs_read(path, buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, strlen(buf_read));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_read_empty_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("empty_file.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "empty_file.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "";
    res = kfs_read(path, buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, strlen(buf));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_read_released_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist_content.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist_content.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    close(fi.fh);
    res = kfs_read(path, buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, -EBADF);
    close(create.fh);
}
END_TEST

START_TEST(kfs_read_chmod) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist_content.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist_content.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0222, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_WRONLY};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    struct fuse_file_info read = {O_RDONLY};
    res = kfs_read(path, buf_read, strlen(buf_read), 0, &read);
    ck_assert_int_eq(res, -ESPIPE);
    close(create.fh);
    close(fi.fh);
    close(read.fh);
}
END_TEST

Suite * kfs_read_suite(void) {
    Suite *suite = suite_create("kfs_read()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_read_setup, kfs_read_teardown);
    tcase_add_test(tcase, kfs_read_exist_file_with_content);
    tcase_add_test(tcase, kfs_read_empty_file);
    tcase_add_test(tcase, kfs_read_released_file);
    tcase_add_test(tcase, kfs_read_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
