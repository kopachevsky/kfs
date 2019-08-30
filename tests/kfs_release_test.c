#include <check.h>
#include <kfs_create.h>
#include <kfs_open.h>
#include <kfs_write.h>
#include <kfs_release.h>

#include "test_main.h"

void kfs_release_setup(void) {
    main_setup();
}

void kfs_release_teardown(void) {
    main_teardown();
}

START_TEST(kfs_release_opened_file) {
    struct fuse_file_info create = init_struct(O_CREAT);
    int res = kfs_create("release_opened_file.txt", 0777, &create);
    fail_if(create.fh == 0);
    ck_assert_int_eq(res, 0);
    struct fuse_file_info fi = init_struct(O_WRONLY);
    res = kfs_open("release_opened_file.txt", &fi);
    fail_if(fi.fh == 0);
    fail_if(res != 0);
    char *buf = "qwerty\n";
    res = kfs_write("release_opened_file.txt",buf, strlen(buf), 0, &fi);
    ck_assert_int_ne(res,0);
    fail_if(fi.fh == 0 );
    res = kfs_release("release_opened_file.txt", &fi);
    ck_assert_int_eq(res,0);
    res = kfs_write("release_opened_file.txt",buf, strlen(buf), 0, &fi);
    ck_assert_int_eq(res,-EBADF);
    remove(str_concat(LOCAL_DISC_CACHE_PATH,"release_opened_file.txt"));
}
END_TEST

Suite *kfs_release_suite(void) {
    Suite *suite = suite_create("kfs_release()");
    TCase *tcase = tcase_create("Test Cases with Setup and Teardown");
    tcase_add_checked_fixture(tcase, kfs_release_setup, kfs_release_teardown);
    tcase_add_test(tcase, kfs_release_opened_file);
    suite_add_tcase(suite, tcase);
    return suite;
}
