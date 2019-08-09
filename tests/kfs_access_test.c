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
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("execute_only.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "execute_only.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0111, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, R_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access(path, X_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_read_only) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("read_only.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "read_only.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0444, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access(path, W_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access(path, R_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_write_only) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("write_only.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "write_only.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0222, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access(path, R_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_access(path, W_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_rwx) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("rwx.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "rwx.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0111, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, R_OK|W_OK|X_OK);
    ck_assert_int_eq(res,-EACCES);
    res = kfs_chmod(path, 0777);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, R_OK|W_OK|X_OK);
    ck_assert_int_eq(res,0);
    close(create.fh);
}
END_TEST

START_TEST(kfs_access_file_existence) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("file_existence.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "file_existence.txt");
    int res = kfs_access(path, F_OK);
    ck_assert_int_eq(res,-ENOENT);
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    res = kfs_access(path, F_OK);
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
