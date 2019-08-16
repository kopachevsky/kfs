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
    char *dir_path = str_concat(LOCAL_DISC_CACHE_PATH, "mydir/");
    struct fuse_file_info create = init_struct(O_CREAT);
    char *file_path = str_concat(dir_path, "first_file.txt");
    res = kfs_create(file_path, 0777, &create);
    ck_assert_int_eq(res,0);
    char *second_file_path = str_concat(dir_path, "second_file.txt");
    res = kfs_create(second_file_path, 0777, &create);
    ck_assert_int_eq(res,0);
    char *second_dir_path = str_concat(dir_path, "second_dir/");
    res = kfs_mkdir(second_dir_path, 0777);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path, &fi);
    ck_assert_int_eq(res, 0);
    res = kfs_readdir(dir_path, test_buf, filler, offset ,&fi);
    ck_assert_int_eq(res, 0);
    ck_assert_int_eq(counter, 5);
    fail_if(file_names == NULL);
    free(dir_path);
    free(file_path);
    free(second_file_path);
    free(second_dir_path);
}
END_TEST

START_TEST(kfs_readdir_released_dir) {
    char path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("released_dir/") + 1];
    strcpy(path, LOCAL_DISC_CACHE_PATH);
    char *dir_path = strcat(path, "released_dir/");
    int res = kfs_mkdir(dir_path, 0777);
    struct fuse_file_info fi = init_struct(O_DIRECTORY);
    res = kfs_opendir(dir_path, &fi);
    res = kfs_releasedir(dir_path, &fi);
    res = kfs_readdir(dir_path,test_buf,filler,offset,&fi);
    ck_assert_int_eq(res,-EBADF);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_readdir_double_call_of_function) {
    int res = kfs_mkdir("double_call/", 0777);
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



