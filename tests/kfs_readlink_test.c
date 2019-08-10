#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_symlink.h>
#include <kfs_mkdir.h>
#include <kfs_read.h>
#include <kfs_readlink.h>

#include "test_main.h"

void kfs_readlink_setup(void) {
    main_setup();
}

void kfs_readlink_teardown(void) {
    main_teardown();
}
START_TEST(kfs_readlink_fs_file) {
    char dir_path_source_file[strlen(LOCAL_DISC_CACHE_PATH) + strlen("source.txt") + 1];
    strcpy(dir_path_source_file, LOCAL_DISC_CACHE_PATH);
    char *source_path = strcat(dir_path_source_file, "source.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create(source_path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open(source_path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(source_path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char dir_path_target_dir[strlen(LOCAL_DISC_CACHE_PATH) + strlen("target/") + strlen(source_path) + 1];
    strcpy(dir_path_target_dir, LOCAL_DISC_CACHE_PATH);
    char *target_path_dir = strcat(dir_path_target_dir, "target/");
    res = kfs_mkdir(target_path_dir, 0777);
    ck_assert_int_eq(res, 0);
    char *target_path = strcat(target_path_dir, "target.txt");
    fail_if(target_path == NULL);
    res = kfs_symlink(source_path,target_path);
    ck_assert_int_eq(res,0);
    char *readlink_buf = "\0";
    char buf_readlink [strlen(readlink_buf)];
    res = kfs_readlink(target_path, buf_readlink, strlen(target_path) + 1);
    ck_assert_int_eq(res, 0);
    char *new_buf = "qwerty123\n";
    res = kfs_write(target_path,new_buf, strlen(new_buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(new_buf));
    char buf_read [strlen(new_buf)];
    res = kfs_read(source_path, buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_readlink_os_fs_file) {
    char dir_path_source_file[strlen(MOUNT_PATH) + strlen("source.txt") + 1];
    strcpy(dir_path_source_file, MOUNT_PATH);
    char *source_path = strcat(dir_path_source_file, "source.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create(source_path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open(source_path, &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write(source_path,buf, strlen(buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(buf));
    char dir_path_target_file[strlen(LOCAL_DISC_CACHE_PATH) + strlen("target.txt") + 1];
    strcpy(dir_path_target_file, LOCAL_DISC_CACHE_PATH);
    char *target_path = strcat(dir_path_target_file, "target.txt");
    fail_if(target_path == NULL);
    res = kfs_symlink(source_path,target_path);
    ck_assert_int_eq(res, 0);
    char *readlink_buf = "\0";
    char buf_readlink [strlen(readlink_buf)];
    res = kfs_readlink(target_path, buf_readlink, strlen(target_path) + 1);
    ck_assert_int_eq(res, 0);
    char *new_buf = "qwerty123\n";
    res = kfs_write(target_path,new_buf, strlen(new_buf), 0, &fi);
    fail_if(fi.fh == 0 );
    ck_assert_int_eq(res, strlen(new_buf));
    char buf_read [strlen(new_buf)];
    res = kfs_read(source_path, buf_read, strlen(new_buf), 0, &fi);
    ck_assert_int_eq(res, strlen(new_buf));
    close(create.fh);
    close(fi.fh);
    close(create.fh);
    close(fi.fh);
}
END_TEST

Suite *kfs_readlink_suite(void) {
    Suite *suite = suite_create("kfs_readlink()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_readlink_setup, kfs_readlink_teardown);
    tcase_add_test(tcase, kfs_readlink_fs_file);
    tcase_add_test(tcase, kfs_readlink_os_fs_file);
    suite_add_tcase(suite, tcase);
    return suite;
}
