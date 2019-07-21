#include <check.h>
#include <stdlib.h>
#include <kfs_common.h>
#include <stdio.h>

#include "kfs_suites.h"

void main_setup(void) {
    char template[] = "/tmp/kfs_tests.XXXXXX";
    LOCAL_DISC_CACHE_PATH = mkdtemp(template);
    if(LOCAL_DISC_CACHE_PATH == NULL) {
        perror("mkdtemp failed: ");
    }
    MOUNT_PATH = "/ext/data1/";
}

void main_teardown(void) {
    remove_directory(LOCAL_DISC_CACHE_PATH);
}

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(kfs_mkdir_suite());
  //  srunner_add_suite(sr, kfs_common_suite());
   // srunner_add_suite(sr, kfs_access_suite());
  //  srunner_add_suite(sr, kfs_read_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_set_log (sr, "test.log");
    srunner_set_xml (sr, "test.xml");
    srunner_run_all(sr, CK_VERBOSE);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
