#include "xglfs_readdir.h"

int xglfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    (void) path;
    (void) offset;
    (void) fi;
    struct dirent* de = glfs_readdir(FH_TO_FD(XGLFS_STATE->g_fh));
    if (de == NULL) {
        return -errno;
    }
    do {
        if (filler(buf, de->d_name, NULL, 0) != 0) {
            return -ENOMEM;
        }
    } while (likely((de = glfs_readdir(FH_TO_FD(XGLFS_STATE->g_fh))) != NULL));
    return 0;
}