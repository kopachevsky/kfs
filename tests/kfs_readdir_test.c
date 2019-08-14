#include <check.h>
#include <kfs_rmdir.h>
#include <kfs_mkdir.h>
#include <kfs_opendir.h>
#include <dirent.h>
#include <kfs_readdir.h>
#include <kfs_releasedir.h>

#include "test_main.h"

void kfs_readdir_setup(void) {
    main_setup();
}

void kfs_readdir_teardown(void) {
    main_teardown();
}

void *test_buf;
const char *test_name;
off_t offset;
const struct stat *test_stbuf;

int filler (void *buf, const char *name,const struct stat *stbuf, off_t off) {
    test_buf = buf;
    test_name = name;
    test_stbuf = stbuf;
    offset = off;
    return 0;
}


START_TEST(kfs_readdir_exsit) {
    int res = kfs_mkdir("exist/", 0777);
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "exist/");
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path, &fi);
    res = kfs_readdir(dir_path,test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,0);
    fail_if(fi.fh == 0);
    free(dir_path);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_readdir_released_dir) {
    int res = kfs_mkdir("exist/", 0777);
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "released_dir/");
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path, &fi);
    res = kfs_releasedir(dir_path, &fi);
    res = kfs_readdir(dir_path,test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,-EBADF);
    free(dir_path);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_readdir_double_call_of_function) {
    int res = kfs_mkdir("exist/", 0777);
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "double_call/");
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path, &fi);
    res = kfs_readdir(dir_path,test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,0);
    res = kfs_readdir(dir_path,test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,-EBADF);
    free(dir_path);
    close(fi.fh);
}
END_TEST

Suite *kfs_readdir_suite(void) {
    Suite *suite = suite_create("kfs_readdir()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_readdir_setup, kfs_readdir_teardown);
    tcase_add_test(tcase, kfs_readdir_exsit);
    tcase_add_test(tcase, kfs_readdir_released_dir);
    tcase_add_test(tcase, kfs_readdir_double_call_of_function);
    suite_add_tcase(suite, tcase);
    return suite;
}



