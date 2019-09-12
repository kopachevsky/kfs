#include "xglfs_fuse_operations.h"

struct fuse_operations xglfs_operations = {
        .getattr = xglfs_getattr,
        .getdir = NULL,
        .mknod = xglfs_mknod,
        .mkdir = xglfs_mkdir,
        .unlink = xglfs_unlink,
        .rmdir = xglfs_rmdir,
        .symlink = xglfs_symlink,
        .rename = xglfs_rename,
        .link = xglfs_link,
        .chmod = xglfs_chmod,
        .chown = xglfs_chown,
        .utime = NULL,
        .open = xglfs_open,
        .release = xglfs_release,
        .setxattr = xglfs_setxattr,
        .getxattr = xglfs_getxattr,
        .removexattr = xglfs_removexattr,
        .opendir = xglfs_opendir,
        .releasedir = xglfs_releasedir,
        .init = xglfs_init,
        .destroy = xglfs_destroy,
        .access = xglfs_access,
        .create = xglfs_create,
        .fgetattr = xglfs_fgetattr,
        .bmap = NULL
};