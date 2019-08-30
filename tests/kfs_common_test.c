#include <check.h>

#include <kfs_common.h>

#include "test_main.h"

void kfs_common_setup(void) {
    MOUNT_PATH = "/ext/data1/";
    LOCAL_DISC_CACHE_PATH = "/local/fuse_cache/";
}

void kfs_common_teardown(void) {

}

START_TEST(kfs_common_local_disc_cache_path_relative) {
        char fpath[PATH_MAX];
        char *cache_path = "dir/file.txt";
        fullpath(fpath, cache_path);
        ck_assert_str_eq("/tmp/CACHE/dir/file.txt", fpath);
}
END_TEST


Suite *kfs_common_suite(void) {
    Suite *s = suite_create("kfs_common()");
    TCase *tc_core = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tc_core, kfs_common_setup, kfs_common_teardown);
    tcase_add_test(tc_core, kfs_common_local_disc_cache_path_relative);
    suite_add_tcase(s, tc_core);

    return s;
}
