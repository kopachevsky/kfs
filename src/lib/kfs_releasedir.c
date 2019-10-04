#include "kfs_releasedir.h"

int kfs_releasedir(const char *path, struct fuse_file_info* fi) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    (void) fpath;
    int fd = closedir((DIR *) (uintptr_t) fi->fh);
    fprintf(stderr,"%s\n", "kfs releaseDIR");
    fprintf(stderr, "%d\n", -errno);
    if (fd == -1) {
        return -errno;
    }
    if (XGLFS_STATE->gluster_api) {
        fd = xglfs_releasedir(path, fi);
        fprintf(stderr,"%s\n", "xglfs releaseDIR");
        fprintf(stderr, "%d\n", -errno);
        if (fd == -1) {
            return -errno;
        }
    }
    return 0;
}