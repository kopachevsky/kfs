#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_write.h>
#include <kfs_read.h>

#include "test_main.h"

void kfs_read_setup(void) {
    main_setup();
}

void kfs_read_teardown(void) {
    main_teardown();
}

START_TEST(kfs_read_exist_file_with_content) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("read_exist_file_with_content.txt", 0777, &create);
    ck_assert_int_eq(res,0);
    fail_if(create.fh == 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("read_exist_file_with_content.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("read_exist_file_with_content.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    res = kfs_read("read_exist_file_with_content.txt", buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, strlen(buf_read));
    close(create.fh);
    close(fi.fh);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"read_exist_file_with_content.txt"));
}
END_TEST

START_TEST(kfs_read_empty_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("read_empty_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("read_empty_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "";
    res = kfs_read("read_empty_file.txt", buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, strlen(buf));
    close(create.fh);
    close(fi.fh);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"read_empty_file.txt"));
}
END_TEST

START_TEST(kfs_read_released_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("read_released_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("read_released_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("read_released_file.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    close(fi.fh);
    res = kfs_read("read_released_file.txt", buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, -EBADF);
    close(create.fh);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"read_released_file.txt"));
}
END_TEST

START_TEST(kfs_read_chmod) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("read_chmod.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_WRONLY);
    res = kfs_open("read_chmod.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("read_chmod.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0);
    ck_assert_int_eq(res, strlen(buf));
    char buf_read [strlen(buf)];
    res = kfs_read("read_chmod.txt", buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, -EBADF);
    close(create.fh);
    close(fi.fh);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"read_chmod.txt"));
}
END_TEST

Suite *kfs_read_suite(void) {
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
