#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_link.h>
#include <kfs_unlink.h>

#include "test_main.h"

void kfs_unlink_setup(void) {
    main_setup();
}

void kfs_unlink_teardown(void) {
    main_teardown();
}
START_TEST(kfs_unlink_fs_files) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("unlink_source.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("unlink_source.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty";
    res = kfs_write("unlink_source.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_link("unlink_source.txt","unlink_target.txt");
    ck_assert_int_eq(res,0);
    res =  remove("unlink_target.txt");
    ck_assert_int_eq(res,-EPERM);
    res = kfs_unlink("unlink_source.txt");
    ck_assert_int_eq(res, 0);
    remove("/tmp/CACHE/unlink_target.txt");
    res = kfs_open("unlink_target.txt", &fi);
    ck_assert_int_eq(res, -ENOENT);
    res = kfs_unlink("unlink_target.txt");
    remove("/tmp/CACHE/unlink_source.txt");
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_unlink_not_exist) {
    char dir_path_source_file[strlen(MOUNT_PATH) + strlen("unlink_source.txt") + 1];
    strcpy(dir_path_source_file, MOUNT_PATH);
    char *source_path = strcat(dir_path_source_file, "unlink_source.txt");
    int res = kfs_unlink(source_path);
    ck_assert_int_eq(res,-ENOENT);
}
END_TEST

Suite *kfs_unlink_suite(void) {
    Suite *suite = suite_create("kfs_unlink()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_unlink_setup, kfs_unlink_teardown);
    tcase_add_test(tcase, kfs_unlink_fs_files);
    tcase_add_test(tcase, kfs_unlink_not_exist);
    suite_add_tcase(suite, tcase);
    return suite;
}
