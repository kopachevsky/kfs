#include <check.h>
#include <kfs_rmdir.h>
#include <kfs_mkdir.h>
#include <kfs_opendir.h>
#include <kfs_create.h>
#include <dirent.h>

#include "test_main.h"

void kfs_opendir_setup(void) {
    main_setup();
}

void kfs_opendir_teardown(void) {
    main_teardown();
}

START_TEST(kfs_opendir_exsit) {
    int res = kfs_mkdir("opendir_exsit/", 0777);
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_opendir("opendir_exsit/",&open);
    ck_assert_int_eq(res,0);
    fail_if(open.fh == 0);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"opendir_exsit/"));
    close(open.fh);
}
END_TEST

START_TEST(kfs_opendir_not_exist) {
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "not_exist/");
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    int res = kfs_opendir(dir_path,&open);
    ck_assert_int_eq(res,-ENOENT);
    free(dir_path);
}
END_TEST

START_TEST(kfs_opendir_not_a_directory) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("opendir_not_a_directory.txt", 0777, &create);
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_opendir("opendir_not_a_directory.txt",&open);
    ck_assert_int_eq(res,-ENOTDIR);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"opendir_not_a_directory.txt"));
    close(create.fh);
}
END_TEST

Suite *kfs_opendir_suite(void) {
    Suite *suite = suite_create("kfs_opendir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_opendir_setup, kfs_opendir_teardown);
    tcase_add_test(tcase, kfs_opendir_exsit);
    tcase_add_test(tcase, kfs_opendir_not_exist);
    tcase_add_test(tcase, kfs_opendir_not_a_directory);
    suite_add_tcase(suite, tcase);
    return suite;
}

