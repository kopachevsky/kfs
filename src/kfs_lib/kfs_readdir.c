#include "kfs_readdir.h"

int kfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) offset;
    (void) fpath;
    set_current_user();
    DIR *dp =(DIR *) (uintptr_t) fi->fh;
    struct dirent *de = readdir(dp);
    if (de == 0) {
        log_errorf("Error kfs_readDIR : %s\n", strerror( errno ));
        return -errno;
    }
    do {
        if (filler(buf, de->d_name, NULL, 0) != 0) {
            return -ENOMEM;
        }
    } while ((de = readdir(dp)) != NULL);
    set_default_user();
    return 0;
}