#include "kfs_opendir.h"

int kfs_opendir(const char* original_path, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    struct kfs_dirp *d = malloc(sizeof(struct kfs_dirp));
    if (d == NULL)
        return -ENOMEM;

    d->dp = opendir(path);
    if (d->dp == NULL) {
        int res = -errno;
        free(d);
        return res;
    }
    d->offset = 0;
    d->entry = NULL;

    free(path);
    fi->fh = (unsigned long) d;
    return 0;
}

