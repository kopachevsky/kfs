#include "kfs.h"

struct fuse_operations kfs_ops =
        {
                .getattr    = kfs_getattr,
                .access     = kfs_access,
                .open       = kfs_open,
                .read       = kfs_read,
                .write      = kfs_write,
                .truncate   = kfs_truncate,
                .release    = kfs_release,
                .readdir    = kfs_readdir,
                .unlink     = kfs_unlink,
                .rename     = kfs_rename,
                .mkdir      = kfs_mkdir
        };


int main(int argc, char *argv[]) {
    getcwd(ABSOLUTE_PATH, sizeof(ABSOLUTE_PATH));
    return fuse_main(argc, argv, &kfs_ops, NULL);
}