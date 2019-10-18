#include "kfs_fallocate.h"

int kfs_fallocate(const char *path, int mode, off_t offset, off_t length, struct fuse_file_info *fi) {
    int fd;
    if (mode) {
        return -EOPNOTSUPP;
    }
    if(fi == NULL){
        fd = open(path, O_WRONLY);
    } else {
        fd = fi->fh;
    }
    if (fd == -1) {
        return -errno;
    }
    int res = -posix_fallocate(fd, offset, length);
    printf("kfs_fallocate execute result : %d\n", res);
    if(fi == NULL) {
        close(fd);
    }
    return res;
}
