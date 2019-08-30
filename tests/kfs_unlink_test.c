#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_link.h>
#include <kfs_mkdir.h>
#include <kfs_read.h>
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
    res = kfs_mkdir("target/", 0777);
    ck_assert_int_eq(res, 0);
    char *target_path = str_concat("target/", "target.txt");
    fail_if(target_path == NULL);
    res = kfs_link("source.txt",target_path);
    ck_assert_int_eq(res,0);
    char buf_read [strlen(buf)];
    res = kfs_read(target_path, buf_read, strlen(buf_read), 0, &fi);
    ck_assert_int_eq(res, strlen(buf));
    res = kfs_unlink("source.txt");
    ck_assert_int_eq(res, 0);
    res =  remove(str_concat(LOCAL_DISC_CACHE_PATH, target_path));
    ck_assert_int_eq(res,0);
    res = kfs_open("source.txt", &fi);
    ck_assert_int_eq(res, -ENOENT);
    rmdir(str_concat(LOCAL_DISC_CACHE_PATH, "target/"));
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"source.txt" ));
    free(target_path);
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_unlink_not_exist) {
    char dir_path_source_file[strlen(MOUNT_PATH) + strlen("source.txt") + 1];
    strcpy(dir_path_source_file, MOUNT_PATH);
    char *source_path = strcat(dir_path_source_file, "source.txt");
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
