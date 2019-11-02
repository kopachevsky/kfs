#include "kfs_releasedir.h"

int kfs_releasedir(const char *path, struct fuse_file_info *fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    set_current_user();
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    set_default_user();
    log_debugf("kfs_releaseDIR execute result : %d\n", fd);
    if (fd == -1) {
        log_debugf("Error kfs_releaseDIR : %s\n", strerror( errno ));
        return -errno;
    }
    return 0;
}