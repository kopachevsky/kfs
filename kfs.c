#include <errno.h>
#include <fuse.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sysexits.h>

#include "kfs.h"
#include "kfs_functions.h"

struct fuse_operations kfs_ops =
        {
                .getattr    = kfs_getattr,
                .access     = kfs_access,
                .open       = kfs_open,
                .read       = kfs_read,
                .write      = kfs_write,
                .getdir     = NULL,
                .utime      = NULL,
                .bmap       = NULL
        };


int main(int argc, char *argv[]) {
    getcwd(ABSOLUTE_PATH, sizeof(ABSOLUTE_PATH));
    return fuse_main(argc, argv, &kfs_ops, NULL);
}