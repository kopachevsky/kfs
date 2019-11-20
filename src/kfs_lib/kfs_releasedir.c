#include "kfs_releasedir.h"

int kfs_releasedir(const char *path, struct fuse_file_info *fi) {
    log_debugf("kfs_releasedir start  %s\n", path);
    char fpath[PATH_MAX_EXTENDED] = {0};
    fullpath(fpath, path);
    log_debugf("    kfs_releasedir fullpath : %s\n", fpath);
    log_debugf("    kfs_releasedir fd : %lu\n", fi->fh);
    (void) fpath;
    set_current_user();
    fuse_context_log();
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    set_default_user();
    if (fd == -1) {
        log_debugf("Error kfs_releasedir : %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("kfs_releasedir exit result : %d\n", fd);
    return 0;
}