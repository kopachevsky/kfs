#include "kfs_readdir.h"

int kfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    log_debugf("kfs_readdir start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_readdir fullpath : %s\n", fpath);
    log_debugf("    kfs_readdir fd : %lu\n", fi->fh);
    (void) offset;
    (void) fpath;
    set_current_user();
    fuse_context_log();
    DIR *dp =(DIR *) (uintptr_t) fi->fh;
    struct dirent *de = readdir(dp);
    if (de == 0) {
        log_errorf("Error kfs_readdir : %s\n", strerror( errno ));
        return -errno;
    }
    do {
        if (filler(buf, de->d_name, NULL, 0) != 0) {
            return -ENOMEM;
        }
    } while ((de = readdir(dp)) != NULL);
    set_default_user();
    log_debugf("kfs_readdir exit result %lu\n", fi->fh);
    return 0;
}