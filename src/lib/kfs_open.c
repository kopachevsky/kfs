#include <kfs_open.h>


int kfs_open(const char *path, struct fuse_file_info *fi) {
    fi->fh = open(strcat(LOCAL_DISC_CACHE_PATH, path), O_CREAT | O_RDWR, S_IRWXU);
    return 0;
}
