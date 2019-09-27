#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_mknod.h>
#include "test_main.h"

void kfs_mknod_setup(void) {
    main_setup();
}

void kfs_mknod_teardown(void) {
    main_teardown();
}

START_TEST(kfs_mknod_txt_file_creation) {
    int res = kfs_mknod("mknod_txt_file_creation.txt", 0777, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open("mknod_txt_file_creation.txt", &open);
    fail_if(open.fh == 0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"mknod_txt_file_creation.txt"));
    close(open.fh);
}
END_TEST

START_TEST(kfs_mknod_no_extension_file_creation) {
    int res = kfs_mknod("mknod_no_extension_file_creation", 0777, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_RDONLY);
    res = kfs_open("mknod_no_extension_file_creation", &open);
    fail_if(open.fh == 0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "mknod_no_extension_file_creation"));
    close(open.fh);
}
END_TEST

START_TEST(kfs_mknod_not_a_file) {
    int res = kfs_mknod("mknod_not_a_file/", 0777, 0);
    ck_assert_int_eq(res,-ENOENT);
}
END_TEST

START_TEST(kfs_mknod_already_exist) {
    int res = kfs_mknod("mknod_already_exist", 0777, 0);
    ck_assert_int_eq(res,0);
    res = kfs_mknod("mknod_already_exist", 0777, 0);
    ck_assert_int_eq(res,-EEXIST);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"mknod_already_exist"));
}
END_TEST

START_TEST(kfs_mknod_chmod) {
    int res = kfs_mknod("readonly.txt", 0444, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_WRONLY);
    res = kfs_open("readonly.txt", &open);
    ck_assert_int_eq(res, -EACCES);
    res = kfs_mknod("wronly.txt", 0222, 0);
    ck_assert_int_eq(res,0);
    res = kfs_open("wronly.txt", &open);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"readonly.txt"));
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "wronly.txt"));
    fail_if(open.fh == 0);
}
END_TEST

Suite *kfs_mknod_suite(void) {
    Suite *suite = suite_create("kfs_mknod()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_mknod_setup, kfs_mknod_teardown);
    tcase_add_test(tcase, kfs_mknod_txt_file_creation);
    tcase_add_test(tcase, kfs_mknod_no_extension_file_creation);
    tcase_add_test(tcase, kfs_mknod_not_a_file);
    tcase_add_test(tcase, kfs_mknod_already_exist);
    tcase_add_test(tcase, kfs_mknod_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
