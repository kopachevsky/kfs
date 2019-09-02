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
    int res = kfs_mkdir("releasedir_exsit/", 0777);
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_opendir("releasedir_exsit/",&open);
    res = kfs_releasedir("releasedir_exsit/", &open);
    ck_assert_int_eq(res,0);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"releasedir_exsit/"));
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
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("releasedir_not_a_directory.txt", 0777, &create);
    struct fuse_file_info open = init_struct(O_DIRECTORY);
    res = kfs_releasedir("releasedir_not_a_directory.txt",&open);
    ck_assert_int_eq(res,-EINVAL);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "releasedir_not_a_directory.txt"));
    close(open.fh);
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

