#include "xglfs_fgetattr.h"

int xglfs_fgetattr(const char *path, struct stat *stbuf,struct fuse_file_info *fi) {
    (void)fi;
    int res = 0;
    if (!strcmp(path, "/")) {
        res = xglfs_getattr(path, stbuf);
    } else {
        res = glfs_fstat(FH_TO_FD(XGLFS_STATE->g_fh), stbuf);
        if (res == -1) {
            return -errno;
        }
    }
    return 0;
}

