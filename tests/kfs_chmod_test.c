#include <check.h>
#include <kfs_chmod.h>
#include <kfs_mkdir.h>
#include <kfs_create.h>
#include <kfs_open.h>

#include "test_main.h"

void kfs_chmod_setup(void) {
    main_setup();
}

void kfs_chmod_teardown(void) {
    main_teardown();
}

START_TEST(kfs_chmod_directory_decrease_permissions) {
    char path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("chmod_directory/") + 1];
    strcpy(path, LOCAL_DISC_CACHE_PATH);
    char *dir_path = strcat(path, "chmod_directory/");
    int res = kfs_mkdir(dir_path, 0777);
    ck_assert_int_eq(res, 0);
    res = kfs_chmod(dir_path, 0111);
    fail_if(res != 0);
    char *path_file = strcat(dir_path, "chmod.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    res = kfs_create(path_file, 0777, &create);
    fail_if(create.fh != 0);
    ck_assert_int_eq(res,-EACCES);
}
END_TEST

START_TEST(kfs_chmod_directory_increase_permissions) {
    char path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("chmod_directory/") + 1];
    strcpy(path, LOCAL_DISC_CACHE_PATH);
    char *dir_path = strcat(path, "chmod_directory/");
    int res = kfs_mkdir(dir_path, 0111);
    ck_assert_int_eq(res, 0);
    res = kfs_chmod(dir_path, 0777);
    fail_if(res != 0);
    char *path_file = strcat(dir_path, "chmod.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    res = kfs_create(path_file, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
}
END_TEST

START_TEST(kfs_chmod_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("chmod.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "chmod.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create(path, 0111, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, -EACCES);
    fail_if(path == NULL);
    res = kfs_chmod(path, 0777);
    fail_if(res != 0);
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, 0);
    close(open.fh);
    res = kfs_chmod(path, 0111);
    fail_if(res != 0);
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, -EACCES);
}
END_TEST

Suite *kfs_chmod_suite(void) {
    Suite *suite = suite_create("kfs_chmod()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_chmod_setup, kfs_chmod_teardown);
    tcase_add_test(tcase, kfs_chmod_directory_decrease_permissions);
    tcase_add_test(tcase, kfs_chmod_directory_increase_permissions);
    tcase_add_test(tcase, kfs_chmod_file);
    suite_add_tcase(suite, tcase);
    return suite;
}
