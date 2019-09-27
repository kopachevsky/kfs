#include <check.h>
#include <kfs_create.h>
#include <kfs_mkdir.h>
#include <kfs_opendir.h>
#include <kfs_readdir.h>
#include <kfs_releasedir.h>
#include <dirent.h>

#include "test_main.h"

void kfs_readdir_setup(void) {
    main_setup();
}

void kfs_readdir_teardown(void) {
    main_teardown();
}

void *test_buf;
static const char *test_name;
off_t offset;
const struct stat *test_stbuf;
static int counter;
const char *file_names[5] = {0, 0, 0, 0, 0};

int filler (void *buf, const char *name, const struct stat *stbuf, off_t off) {
    file_names[counter] = name;
    counter++;
    test_buf = buf;
    test_name = name;
    test_stbuf = stbuf;
    offset = off;
    return 0;
}

START_TEST(kfs_readdir_exsit) {
    int res = kfs_mkdir("mydir/", 0777);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info create = init_struct(O_CREAT);
    char *file_path = str_concat("mydir/", "first_file.txt");
    res = kfs_create(file_path, 0777, &create);
    ck_assert_int_eq(res,0);
    char *second_file_path = str_concat("mydir/", "second_file.txt");
    res = kfs_create(second_file_path, 0777, &create);
    ck_assert_int_eq(res,0);
    char *second_dir_path = str_concat("mydir/", "second_dir/");
    res = kfs_mkdir(second_dir_path, 0777);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir("mydir/", &fi);
    ck_assert_int_eq(res, 0);
    res = kfs_readdir("mydir/", test_buf, filler, offset ,&fi);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(counter, 5);
    fail_unless(strcmp(file_names[0],"second_file.txt") == 0);
    fail_unless(strcmp(file_names[2],"second_dir") == 0);
    fail_unless(strcmp(file_names[4],"first_file.txt") == 0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"mydir/first_file.txt"));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"mydir/second_file.txt"));
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"mydir/second_dir/"));
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"mydir/"));
    free(file_path);
    free(second_file_path);
    free(second_dir_path);
}
END_TEST

START_TEST(kfs_readdir_released_dir) {
    int res = kfs_mkdir("readdir_released_dir/", 0777);
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir("readdir_released_dir/", &fi);
    res = kfs_releasedir("readdir_released_dir/", &fi);
    res = kfs_readdir("readdir_released_dir/",test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,-EBADF);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"readdir_released_dir/"));
    close(fi.fh);
}
END_TEST

START_TEST(kfs_readdir_double_call_of_function) {
    int res = kfs_mkdir("double_call/", 0777);
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir("double_call/", &fi);
    res = kfs_readdir("double_call/",test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,0);
    res = kfs_readdir("double_call/",test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,-errno);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"double_call/"));
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



