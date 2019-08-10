#include <kfs_getattr.h>

int kfs_getattr(const char *original_path, struct stat *st) {
    char *path = local_disk_cache_path(original_path);
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time( NULL );
    st->st_mtime = time( NULL );
    if (strcmp(path, "/") == 0) {
        st->st_mode = S_IFDIR | S_IRWXU;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | S_IRWXU;
        st->st_nlink = 1;
    }
    free(path);
    return 0;
}
