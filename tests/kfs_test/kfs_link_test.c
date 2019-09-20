#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_link.h>
#include <kfs_unlink.h>

#include "test_main.h"

void kfs_link_setup(void) {
    main_setup();
}

void kfs_link_teardown(void) {
    main_teardown();
}
START_TEST(kfs_link_fs_files) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("source.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open("source.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty";
    res = kfs_write("source.txt",buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_link("source.txt","target.txt");
    ck_assert_int_eq(res,0);
    res = kfs_unlink("target.txt");
    close(create.fh);
    close(fi.fh);
    remove("/tmp/CACHE/target.txt");
    remove("/tmp/CACHE/source.txt");
}
END_TEST

START_TEST(kfs_link_chmod) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("link_chmod.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    char *target_path = "/home/chmod.txt";
    res = kfs_link("link_chmod.txt", target_path);
    ck_assert_int_eq(res, -ENOENT);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"link_chmod.txt"));
}
END_TEST

Suite *kfs_link_suite(void) {
    Suite *suite = suite_create("kfs_link()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_link_setup, kfs_link_teardown);
    tcase_add_test(tcase, kfs_link_fs_files);
    tcase_add_test(tcase, kfs_link_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
