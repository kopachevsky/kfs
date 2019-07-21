#include <check.h>

#include <kfs_common.h>

#include "test_main.h"

void kfs_common_setup(void) {

}

void kfs_common_teardown(void) {

}

START_TEST(kfs_common_base) {
    MOUNT_PATH = "/ext/";
    LOCAL_DISC_CACHE_PATH = "/local/disc/cache";
    char * cache_path = local_disk_cache_path("/home/kopachevsky/file.txt");
    ck_assert_str_eq("/local/disck/cache/data/file.txt", cache_path);
}
END_TEST

Suite *kfs_common_suite(void) {
    Suite *s = suite_create("kfs_common()");
    TCase *tc_core = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tc_core, kfs_common_setup, kfs_common_teardown);
    tcase_add_test(tc_core, kfs_common_base);
    suite_add_tcase(s, tc_core);

    return s;
}
