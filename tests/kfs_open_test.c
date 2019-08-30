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
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("open_exist.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = init_struct(O_RDONLY|O_WRONLY);
    res = kfs_open("open_exist.txt", &open);
    fail_if(open.fh == 0);
    fail_if(res != 0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "open_exist.txt"));
}
END_TEST

START_TEST(kfs_open_not_exist) {
    struct fuse_file_info open = init_struct(O_RDONLY|O_WRONLY);
    int res = kfs_open("not_exist.txt", &open);
    ck_assert_int_eq(res, -ENOENT);
}
END_TEST

START_TEST(kfs_open_chmod) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("open_chmod.txt", 0111, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open("open_chmod.txt", &open);
    ck_assert_int_eq(res, -EACCES);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "open_chmod.txt"));
}
END_TEST

START_TEST(kfs_open_read) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("open_read.txt", 0444, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open_write = init_struct(O_WRONLY);
    res = kfs_open("open_read.txt", &open_write);
    ck_assert_int_eq(res, -EACCES);
    struct fuse_file_info open_read = {O_RDONLY};
    res = kfs_open("open_read.txt", &open_read);
    ck_assert_int_eq(res, 0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"open_read.txt"));
}
END_TEST

START_TEST(kfs_open_write) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("open_write.txt", 0222, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open_read = {O_RDONLY};
    res = kfs_open("open_write.txt", &open_read);
    ck_assert_int_eq(res, -EACCES);
    struct fuse_file_info open_write = init_struct(O_WRONLY);
    res = kfs_open("open_write.txt", &open_write);
    ck_assert_int_eq(res, 0);
    fail_if("open_write.txt" == NULL);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"open_write.txt"));
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
