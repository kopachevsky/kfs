#include <check.h>
#include <stdlib.h>
#include "kfs_suites.h"

int main(void) {
    int number_failed;
    SRunner *sr;

    sr = srunner_create(kfs_access_suite());
    srunner_add_suite(sr, kfs_read_suite());
    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_set_log (sr, "test.log");
    srunner_set_xml (sr, "test.xml");
    srunner_run_all(sr, CK_VERBOSE);

    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
