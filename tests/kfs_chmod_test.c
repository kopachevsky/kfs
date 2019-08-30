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
    int res = kfs_mkdir("chmod_directory_decrease_permissions/", 0777);
    ck_assert_int_eq(res, 0);
    res = kfs_chmod("chmod_directory_decrease_permissions/", 0111);
    fail_if(res != 0);
    char *path_file = str_concat("chmod_directory_decrease_permissions/", "chmod.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    res = kfs_create(path_file, 0777, &create);
    fail_if(create.fh != 0);
    ck_assert_int_eq(res,-EACCES);
    free(path_file);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"chmod_directory_decrease_permissions/"));
}
END_TEST

START_TEST(kfs_chmod_directory_increase_permissions) {
    int res = kfs_mkdir("chmod_directory_increase_permissions/", 0111);
    ck_assert_int_eq(res, 0);
    res = kfs_chmod("chmod_directory_increase_permissions/", 0777);
    fail_if(res != 0);
    char *path_file = str_concat("chmod_directory_increase_permissions/", "chmod.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    res = kfs_create(path_file, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, path_file));
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"chmod_directory_increase_permissions/"));
    free(path_file);
}
END_TEST

START_TEST(kfs_chmod_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("chmod_file.txt", 0111, &create);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open("chmod_file.txt", &open);
    ck_assert_int_eq(res, -EACCES);
    res = kfs_chmod("chmod_file.txt", 0777);
    fail_if(res != 0);
    res = kfs_open("chmod_file.txt", &open);
    ck_assert_int_eq(res, 0);
    close(open.fh);
    res = kfs_chmod("chmod_file.txt", 0111);
    fail_if(res != 0);
    res = kfs_open("chmod_file.txt", &open);
    ck_assert_int_eq(res, -EACCES);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"chmod_file.txt"));
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
