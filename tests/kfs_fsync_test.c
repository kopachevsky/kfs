#include <check.h>
#include <kfs_open.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_fsync.h>
#include <kfs_flush.h>

#include "test_main.h"

void kfs_fsync_setup(void) {
    main_setup();
}

void kfs_fsync_teardown(void) {
    main_teardown();
}

START_TEST(kfs_fsync_opened_file) {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("opened.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "opened.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    ck_assert_int_eq(res,0);
    fail_if(fi.fh == 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_fsync(path, 0, &fi);
    ck_assert_int_eq(res,0);
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_fsync_flushed_file)  {
    char dir_path[strlen(LOCAL_DISC_CACHE_PATH) + strlen("flushed.txt") + 1];
    strcpy(dir_path, LOCAL_DISC_CACHE_PATH);
    char *path = strcat(dir_path, "flushed.txt");
    struct fuse_file_info create = {O_CREAT};
    int res = kfs_create(path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = {O_RDWR};
    res = kfs_open(path, &fi);
    ck_assert_int_eq(res,0);
    fail_if(fi.fh == 0);
    char *buf = "qwerty\n";
    res = kfs_write(path,buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_flush(path, &fi);
    ck_assert_int_eq(res,0);
    res = kfs_fsync(path, 0, &fi);
    ck_assert_int_eq(res,-EBADF);
    close(create.fh);
}
END_TEST


Suite *kfs_fsync_suite(void) {
    Suite *suite = suite_create("kfs_fsync()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_fsync_setup, kfs_fsync_teardown);
    tcase_add_test(tcase, kfs_fsync_opened_file);
    tcase_add_test(tcase, kfs_fsync_flushed_file);
    suite_add_tcase(suite, tcase);
    return suite;
}


