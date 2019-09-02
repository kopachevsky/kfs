#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_write.h>

#include "test_main.h"

void kfs_write_setup(void) {
    main_setup();
}

void kfs_write_teardown(void) {
    main_teardown();
}

START_TEST(kfs_write_exist) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("kfs_write_exist.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_WRONLY);
    res = kfs_open("kfs_write_exist.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("kfs_write_exist.txt", buf, strlen(buf),0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    close(create.fh);
    close(fi.fh);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"kfs_write_exist.txt"));
}
END_TEST

START_TEST(kfs_write_file_not_opened) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("write_file_not_opened.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_RDWR|O_RDONLY|O_WRONLY);
    res = kfs_open("write_file_not_opened.txt", &fi);
    ck_assert_int_eq(res, 0);
    close(fi.fh);
    char *buf = "qwerty";
    res = kfs_write("write_file_not_opened.txt",buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, -EBADF);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"write_file_not_opened.txt"));
}
END_TEST

Suite *kfs_write_suite(void) {
    Suite *suite = suite_create("kfs_write()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_write_setup, kfs_write_teardown);
    tcase_add_test(tcase, kfs_write_exist);
    tcase_add_test(tcase, kfs_write_file_not_opened);
    suite_add_tcase(suite, tcase);
    return suite;
}
