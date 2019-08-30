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
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("fsync_opened_file.txt", 0777, &create);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("fsync_opened_file.txt", &fi);
    char *buf = "qwerty\n";
    res = kfs_write("fsync_opened_file.txt",buf, strlen(buf), 0, &fi);
    res = kfs_fsync("fsync_opened_file.txt", 0, &fi);
    ck_assert_int_eq(res,0);
    remove(str_concat(LOCAL_DISC_CACHE_PATH, "fsync_opened_file.txt"));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_fsync_flushed_file)  {
    struct fuse_file_info create = init_struct(O_CREAT);;
    int res = kfs_create("fsync_flushed_file.txt", 0777, &create);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("fsync_flushed_file.txt", &fi);
    char *buf = "qwerty\n";
    res = kfs_write("fsync_flushed_file.txt",buf, strlen(buf), 0, &fi);
    res = kfs_flush("fsync_flushed_file.txt", &fi);
    res = kfs_fsync("fsync_flushed_file.txt", 0, &fi);
    ck_assert_int_eq(res,-EBADF);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"fsync_flushed_file.txt"));
    close(fi.fh);
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


