#include <check.h>
#include <kfs_access.h>
#include <kfs_create.h>
#include <kfs_chmod.h>

#include "test_main.h"

void kfs_access_setup(void) {
    main_setup();
}

void kfs_access_teardown(void) {
    main_teardown();
}

START_TEST(kfs_access_execute_only) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("execute_only.txt", 0111, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access("execute_only.txt", R_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access("execute_only.txt", X_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_read_only) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("read_only.txt", 0444, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access("read_only.txt", X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access("read_only.txt", W_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access("read_only.txt", R_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_write_only) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("write_only.txt", 0222, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access("write_only.txt", X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access("write_only.txt", R_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access("write_only.txt", W_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_rwx) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("rwx.txt", 0111, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access("rwx.txt", R_OK|W_OK|X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_chmod("rwx.txt", 0777);
    ck_assert_int_eq(res,0);
    res = kfs_access("rwx.txt", R_OK|W_OK|X_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_file_existence) {
    int res = kfs_access("file_existence.txt", F_OK);
    ck_assert_int_eq(res,-ENOENT);
    struct fuse_file_info create = init_struct(O_CREAT);
    res = kfs_create("file_existence.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access("file_existence.txt", F_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

Suite *kfs_access_suite(void) {
    Suite *suite = suite_create("kfs_access()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_access_setup, kfs_access_teardown);
    tcase_add_test(tcase, kfs_access_execute_only);
    tcase_add_test(tcase, kfs_access_read_only);
    tcase_add_test(tcase, kfs_access_write_only);
    tcase_add_test(tcase, kfs_access_rwx);
    tcase_add_test(tcase, kfs_access_file_existence);
    suite_add_tcase(suite, tcase);
    return suite;
}
