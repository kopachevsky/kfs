#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_write.h>
#include <kfs_truncate.h>
#include <kfs_read.h>
#include <kfs_mkdir.h>
#include <stdio.h>

#include "test_main.h"

void kfs_truncate_setup(void) {
    main_setup();
}

void kfs_truncate_teardown(void) {
    main_teardown();
}

START_TEST(kfs_truncate_increase_size_of_exist_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("truncate_increase_size_of_exist_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("truncate_increase_size_of_exist_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("truncate_increase_size_of_exist_file.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "qwery000000000000\n";
    res = kfs_truncate("truncate_increase_size_of_exist_file.txt", strlen(new_buf));
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read("truncate_increase_size_of_exist_file.txt", buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"truncate_increase_size_of_exist_file.txt"));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_truncate_decrease_size_of_exist_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("truncate_decrease_size_of_exist_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("truncate_decrease_size_of_exist_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("truncate_decrease_size_of_exist_file.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "q\n";
    res = kfs_truncate("truncate_decrease_size_of_exist_file.txt", strlen(new_buf));
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read("truncate_decrease_size_of_exist_file.txt", buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"truncate_decrease_size_of_exist_file.txt"));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_trucate_not_exist_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("not_exist.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "not_exist.txt");
    char *new_buf = "qwery000000000000\n";
    int res = kfs_truncate(path, strlen(new_buf));
    ck_assert_int_eq(res,-ENOENT);
}
END_TEST

START_TEST(kfs_truncate_not_file) {
    int res = kfs_mkdir("truncate_not_file/", 0777);
    ck_assert_int_eq(res,0);
    char *new_buf = "000000000000\n";
    res = kfs_truncate("truncate_not_file/", strlen(new_buf));
    ck_assert_int_eq(res,-EISDIR);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH,"truncate_not_file/"));
}
END_TEST

START_TEST(kfs_truncate_chmod) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("truncate_chmod.txt", 0111, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    char *new_buf = "000000000000\n";
    res = kfs_truncate("truncate_chmod.txt", strlen(new_buf));
    ck_assert_int_eq(res,-EACCES);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"truncate_chmod.txt"));
    close(create.fh);
}
END_TEST

Suite *kfs_truncate_suite(void) {
    Suite *suite = suite_create("kfs_truncate()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_truncate_setup, kfs_truncate_teardown);
    tcase_add_test(tcase, kfs_truncate_increase_size_of_exist_file);
    tcase_add_test(tcase, kfs_truncate_decrease_size_of_exist_file);
    tcase_add_test(tcase, kfs_trucate_not_exist_file);
    tcase_add_test(tcase, kfs_truncate_not_file);
    tcase_add_test(tcase, kfs_truncate_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
