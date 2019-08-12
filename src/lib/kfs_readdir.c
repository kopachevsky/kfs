#include <kfs_readdir.h>

int kfs_readdir(const char *original_path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {
    char *path = local_disk_cache_path(original_path);
    (void) path;
    DIR *dp;
    struct dirent *de;
    dp = (DIR *) (uintptr_t) fi->fh;
    de = readdir(dp);
    if (de == NULL) {
        return -errno;
    }
    do {
        if (filler(buf, de->d_name, NULL, 0) != 0) {
            return -ENOMEM;
        }
    } while ((de = readdir(dp)) != NULL);
    return 0;
}