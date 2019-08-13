#include <check.h>
#include <stdlib.h>
#include <kfs_common.h>
#include <stdio.h>

#include "kfs_suites.h"

struct fuse_file_info init_struct(int flag) {
    struct fuse_file_info s = {0};
    s.flags = flag;
    return  s;
}

void main_setup(void) {
    MOUNT_PATH = "/ext/data1/";

    char template[] = "/tmp/kfs_tests.XXXXXX";
    char *tmp_file = str_concat(mkdtemp(template), "/");
    if(tmp_file == NULL) {
        perror("mkdtemp failed: ");
    }
    LOCAL_DISC_CACHE_PATH = malloc(sizeof(template));
    strcpy(LOCAL_DISC_CACHE_PATH, tmp_file);
    free(tmp_file);
}

void main_teardown(void) {
    remove_directory(LOCAL_DISC_CACHE_PATH);
    free(LOCAL_DISC_CACHE_PATH);
}

int main(void) {
    int number_failed;
    SRunner *sr;
    sr = srunner_create(kfs_rmdir_suite());
//    srunner_add_suite(sr, kfs_common_suite());
//    srunner_add_suite(sr, kfs_mkdir_suite());
//    srunner_add_suite(sr, kfs_open_suite());
//    srunner_add_suite(sr, kfs_create_suite());
//    srunner_add_suite(sr, kfs_access_suite());
//    srunner_add_suite(sr, kfs_read_suite());
//    srunner_add_suite(sr, kfs_write_suite());
//    srunner_add_suite(sr, kfs_release_suite());
//    srunner_add_suite(sr, kfs_chmod_suite());
//    srunner_add_suite(sr, kfs_link_suite());
//    srunner_add_suite(sr, kfs_unlink_suite());
//    srunner_add_suite(sr, kfs_rename_suite());
//    srunner_add_suite(sr, kfs_symlink_suite());
//    srunner_add_suite(sr, kfs_flush_suite());
//    srunner_add_suite(sr, kfs_truncate_suite());
//    srunner_add_suite(sr, kfs_ftruncate_suite());
//    srunner_add_suite(sr, kfs_readlink_suite());
//    srunner_add_suite(sr, kfs_fsync_suite());
//    srunner_add_suite(sr, kfs_opendir_suite());
    srunner_add_suite(sr, kfs_mknod_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_set_log (sr, "test.log");
    srunner_set_xml (sr, "test.xml");
    srunner_run_all(sr, CK_VERBOSE);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
