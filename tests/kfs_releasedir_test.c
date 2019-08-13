#include <check.h>
#include <kfs_rmdir.h>
#include <kfs_mkdir.h>
#include <kfs_opendir.h>
#include <kfs_create.h>
#include <kfs_releasedir.h>
#include <dirent.h>

#include "test_main.h"

void kfs_releasedir_setup(void) {
    main_setup();
}

void kfs_releasedir_teardown(void) {
    main_teardown();
}

START_TEST(kfs_releasedir_exsit) {
    int res = kfs_mkdir("exist/", 0777);
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "exist/");
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path,&open);
    res = kfs_releasedir(dir_path, &open);
    ck_assert_int_eq(res,0);
    free(dir_path);
    close(open.fh);
}
END_TEST

START_TEST(kfs_releasedir_not_exist) {
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "not_exist/");
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    int res = kfs_releasedir(dir_path, &open);
    ck_assert_int_eq(res,-EINVAL);
    free(dir_path);
}
END_TEST

START_TEST(kfs_releasedir_not_a_directory) {
    int res = kfs_mkdir("dir/", 0777);
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "dir/");
    struct fuse_file_info create = init_struct(O_CREAT);
    char *file_path = str_concat(dir_path, "not_a_dir.txt");
    res = kfs_create(file_path, 0777, &create);
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_releasedir(file_path,&open);
    ck_assert_int_eq(res,-EINVAL);
    free(dir_path);
    free(file_path);
}
END_TEST

Suite *kfs_releasedir_suite(void) {
    Suite *suite = suite_create("kfs_releasedir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_releasedir_setup, kfs_releasedir_teardown);
    tcase_add_test(tcase, kfs_releasedir_exsit);
    tcase_add_test(tcase, kfs_releasedir_not_exist);
    tcase_add_test(tcase, kfs_releasedir_not_a_directory);
    suite_add_tcase(suite, tcase);
    return suite;
}
