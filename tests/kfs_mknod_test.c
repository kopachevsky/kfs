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
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("creation.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "creation.txt");
    int res = kfs_mknod(path, 0777, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open(path, &open);
    fail_if(open.fh == 0);
    close(open.fh);
}
END_TEST

START_TEST(kfs_mknod_no_extension_file_creation) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("no_extension") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "no_extension");
    int res = kfs_mknod(path, 0777, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_RDONLY);
    res = kfs_open(path, &open);
    fail_if(open.fh == 0);
    close(open.fh);
}
END_TEST

START_TEST(kfs_mknod_not_a_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("not_a_file/") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "not_a_file/");
    int res = kfs_mknod(path, 0777, 0);
    ck_assert_int_eq(res,-ENOENT);
}
END_TEST

START_TEST(kfs_mknod_already_exist) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("already_exist") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "already_exist");
    int res = kfs_mknod(path, 0777, 0);
    ck_assert_int_eq(res,0);
    res = kfs_mknod(path, 0777, 0);
    ck_assert_int_eq(res,-EEXIST);
}
END_TEST
START_TEST(kfs_mknod_chmod) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("readonly.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "readonly.txt");
    int res = kfs_mknod(path, 0444, 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_WRONLY);
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, -EACCES);
    char dir_path_renamed[strlen(LOCAL_DISC_CACHE_PATH) + strlen("wronly.txt") + 1];
    strcpy(dir_path_renamed, LOCAL_DISC_CACHE_PATH);
    char *wronly_path = strcat(dir_path_renamed, "wronly.txt");
    res = kfs_mknod(wronly_path, 0222, 0);
    ck_assert_int_eq(res,0);
    res = kfs_open(wronly_path, &open);
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
