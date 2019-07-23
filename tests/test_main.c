#include <check.h>
#include <stdlib.h>
#include <kfs_common.h>
#include <stdio.h>

#include "kfs_suites.h"

void main_setup(void) {
    MOUNT_PATH = "/ext/data1/";

    char template[] = "/tmp/kfs_tests.XXXXXX";
    char *tmp_file = mkdtemp(template);
    if(tmp_file == NULL) {
        perror("mkdtemp failed: ");
    }
    LOCAL_DISC_CACHE_PATH = malloc(sizeof(template));
    strcpy(LOCAL_DISC_CACHE_PATH, tmp_file);
}

void main_teardown(void) {
    remove_directory(LOCAL_DISC_CACHE_PATH);
    free(LOCAL_DISC_CACHE_PATH);
}

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(kfs_mkdir_suite());
   // srunner_add_suite(sr, kfs_common_suite());
   // srunner_add_suite(sr, kfs_access_suite());
//    srunner_add_suite(sr, kfs_read_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_set_log (sr, "test.log");
    srunner_set_xml (sr, "test.xml");
    srunner_run_all(sr, CK_VERBOSE);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
