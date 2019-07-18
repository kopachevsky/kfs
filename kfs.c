#include "kfs.h"

struct fuse_operations kfs_ops =
        {
                .getattr    = kfs_getattr,
                .access     = kfs_access,
                .open       = kfs_open,
                .read       = kfs_read,
                .write      = kfs_write,
                .truncate   = kfs_truncate,
                .release    = kfs_release
//                .getdir     = NULL,
//                .utime      = NULL,
//                .bmap       = NULL
        };


int main(int argc, char *argv[]) {
    getcwd(ABSOLUTE_PATH, sizeof(ABSOLUTE_PATH));
    return fuse_main(argc, argv, &kfs_ops, NULL);
}