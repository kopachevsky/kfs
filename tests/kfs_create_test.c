#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <stdio.h>

#include "test_main.h"

void kfs_create_setup(void) {
    main_setup();
}

void kfs_create_teardown(void) {
    main_teardown();
}

START_TEST(kfs_create_creation) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("creation.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "creation.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = {O_RDWR};
    res = kfs_open(path, &open);
    fail_if(open.fh == 0);
    ck_assert_int_eq(res, 0);
    close(create.fh);
    close(open.fh);
}
END_TEST

START_TEST(kfs_create_exist) {
    struct fuse_file_info fi = {O_CREAT|O_EXCL};
    int res = kfs_create("exist.txt", 0777, &fi);
    ck_assert_int_eq(res, 0);
    res = kfs_create("exist.txt", 0777, &fi);
    ck_assert_int_eq(res, -EEXIST);
}
END_TEST

START_TEST(kfs_create_chmod) {
    struct fuse_file_info fi = {O_CREAT};
    int res = kfs_create("chmod.txt", 0111, &fi);
    ck_assert_int_eq(res, 0);
    res = kfs_create("chmod.txt", 0777, &fi);
    ck_assert_int_eq(res, -EACCES);
}
END_TEST

Suite * kfs_create_suite(void) {
    Suite *suite = suite_create("kfs_create()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_create_setup, kfs_create_teardown);
    tcase_add_test(tcase, kfs_create_creation);
    tcase_add_test(tcase, kfs_create_exist);
    tcase_add_test(tcase, kfs_create_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
