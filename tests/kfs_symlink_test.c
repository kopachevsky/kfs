#include <check.h>
#include <kfs_create.h>
#include <kfs_write.h>
#include <kfs_open.h>
#include <kfs_unlink.h>
#include <kfs_symlink.h>
#include <kfs_mkdir.h>

#include "test_main.h"

void kfs_symlink_setup(void) {
    main_setup();
}

void kfs_symlink_teardown(void) {
    main_teardown();
}
START_TEST(kfs_symlink_fs_files) {
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
    res = remove(source_path);
    ck_assert_int_eq(res, 0);
    res = kfs_open(target_path, &fi);
    ck_assert_int_eq(res, -ENOENT);
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_symlink_os_fs_files) {
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
    res = kfs_unlink(source_path);
    ck_assert_int_eq(res, 0);
    res = kfs_open(target_path, &fi);
    ck_assert_int_eq(res, -ENOENT);
    close(create.fh);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_symlink_file_to_dir) {
    char dir_path_source_file[strlen(LOCAL_DISC_CACHE_PATH) + strlen("source/") + 1];
    strcpy(dir_path_source_file, LOCAL_DISC_CACHE_PATH);
    char *source_path = strcat(dir_path_source_file, "source/");
    int res = mkdir(source_path, 0777);
    ck_assert_int_eq(res,0);
    char dir_path_target_dir[strlen(LOCAL_DISC_CACHE_PATH) + strlen("target/") + strlen(source_path) + 1];
    strcpy(dir_path_target_dir, LOCAL_DISC_CACHE_PATH);
    char *target_path_dir = strcat(dir_path_target_dir, "target/");
    res = kfs_mkdir(target_path_dir, 0777);
    ck_assert_int_eq(res, 0);
    char *target_path = strcat(target_path_dir, "target.txt");
    res = symlink(source_path, target_path);
    ck_assert_int_eq(res,0);
    struct fuse_file_info fi = init_struct(O_RDWR);
    res = kfs_open(target_path, &fi);
    ck_assert_int_eq(res,-EISDIR);
    res = rmdir(source_path);
    ck_assert_int_eq(res,0);
    res = kfs_open(target_path, &fi);
    ck_assert_int_eq(res,-ENOENT);
    close(fi.fh);
}
END_TEST

START_TEST(kfs_symlink_chmod) {
    char dir_path_source_file[strlen(LOCAL_DISC_CACHE_PATH) + strlen("target.txt") + 1];
    strcpy(dir_path_source_file, LOCAL_DISC_CACHE_PATH);
    char *source_path = strcat(dir_path_source_file, "target.txt");
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create(source_path, 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res,0);
    char *target_path = "/home/chmod.txt";
    res = kfs_symlink(source_path, target_path);
    ck_assert_int_eq(res, -EACCES);
}
END_TEST

Suite *kfs_symlink_suite(void) {
    Suite *suite = suite_create("kfs_symlink()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_symlink_setup, kfs_symlink_teardown);
    tcase_add_test(tcase, kfs_symlink_fs_files);
    tcase_add_test(tcase, kfs_symlink_os_fs_files);
    tcase_add_test(tcase, kfs_symlink_file_to_dir);
    tcase_add_test(tcase, kfs_symlink_chmod);
    suite_add_tcase(suite, tcase);
    return suite;
}
