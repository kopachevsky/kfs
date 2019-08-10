#include <check.h>
#include "kfs_rename.h"
#include <kfs_create.h>
#include <kfs_open.h>

#include "test_main.h"

void kfs_rename_setup(void) {
    main_setup();
}

void kfs_rename_teardown(void) {
    main_teardown();
}

START_TEST(kfs_rename_exist_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("created_file.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "created_file.txt.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    char dir_path_renamed[strlen(LOCAL_DISC_CACHE_PATH) + strlen("renamed_file.txt") + 1];
    strcpy(dir_path_renamed, LOCAL_DISC_CACHE_PATH);
    char *renamed_file_path = strcat(dir_path_renamed, "renamed_file.txt");
    res = kfs_rename(path, renamed_file_path);
    ck_assert_int_eq(res,0);
    struct fuse_file_info open = init_struct(O_RDWR);
    res = kfs_open(path, &open);
    ck_assert_int_eq(res, -ENOENT);
    res = kfs_open(renamed_file_path, &open);
    fail_if(open.fh == 0);
    ck_assert_int_eq(res, 0);
    close(create.fh);
    close(open.fh);
}
END_TEST

START_TEST(kfs_rename_not_exist_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("not_exist_file.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "not_exist_file.txt.txt");
    char dir_path_renamed[strlen(LOCAL_DISC_CACHE_PATH) + strlen("renamed_file.txt") + 1];
    strcpy(dir_path_renamed, LOCAL_DISC_CACHE_PATH);
    char *renamed_file_path = strcat(dir_path_renamed, "renamed_file.txt");
    int res = kfs_rename(path, renamed_file_path);
    ck_assert_int_eq(res,-ENOENT);
}
END_TEST

Suite * kfs_rename_suite(void) {
    Suite *suite = suite_create("kfs_rename()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_rename_setup, kfs_rename_teardown);
    tcase_add_test(tcase, kfs_rename_exist_file);
    tcase_add_test(tcase, kfs_rename_not_exist_file);
    suite_add_tcase(suite, tcase);
    return suite;
}
