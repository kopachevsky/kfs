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
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("exist.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "exist.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_WRONLY,0,0,1,1,0,1,1,27,0,0};
    res = kfs_open(path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_write_file_not_opened) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("not_opened.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "not_opened.txt");
    struct fuse_file_info create = {O_CREAT,0,0,1,1,0,1,1,27,0,0};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR,0,0,1,1,0,1,1,27,0,0};
    res = kfs_open(path, &fi);
    ck_assert_int_eq(res, 0);
    close(fi.fh);
    char *buf = "qwerty";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, -EBADF);
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
