#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_read.h>
#include <kfs_ftruncate.h>

#include "test_main.h"

void kfs_ftruncate_setup(void) {
    main_setup();
}

void kfs_ftruncate_teardown(void) {
    main_teardown();
}

START_TEST(kfs_ftruncate_increase_size_of_exist_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("ftruncate_increase_size_of_exist_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("ftruncate_increase_size_of_exist_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("ftruncate_increase_size_of_exist_file.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "qwery000000000000\n";
    res = kfs_ftruncate("ftruncate_increase_size_of_exist_file.txt", strlen(new_buf), &fi);
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read("ftruncate_increase_size_of_exist_file.txt", buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"ftruncate_increase_size_of_exist_file.txt"));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_ftruncate_decrease_size_of_exist_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("ftruncate_decrease_size_of_exist_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("ftruncate_decrease_size_of_exist_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("ftruncate_decrease_size_of_exist_file.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char *new_buf = "q\n";
    res = kfs_ftruncate("ftruncate_decrease_size_of_exist_file.txt", strlen(new_buf), &fi);
    ck_assert_int_eq(res,0);
    char buf_read [strlen(new_buf)];
    res = kfs_read("ftruncate_decrease_size_of_exist_file.txt", buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"ftruncate_decrease_size_of_exist_file.txt"));
    close(create.fh);
    close(fi.fh);
}
END_TEST

Suite *kfs_ftruncate_suite(void) {
    Suite *suite = suite_create("kfs_ftruncate()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_ftruncate_setup, kfs_ftruncate_teardown);
    tcase_add_test(tcase, kfs_ftruncate_increase_size_of_exist_file);
    tcase_add_test(tcase, kfs_ftruncate_decrease_size_of_exist_file);
    suite_add_tcase(suite, tcase);
    return suite;
}