#include <kfs_getattr.h>

int kfs_getattr(const char *path, struct stat *st) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    st->st_uid = getuid();
    st->st_gid = getgid();
    st->st_atime = time( NULL );
    st->st_mtime = time( NULL );
    if (strcmp(fpath, "/") == 0) {
        st->st_mode = S_IFDIR | S_IRWXU;
        st->st_nlink = 2;
    } else {
        st->st_mode = S_IFREG | S_IRWXU;
        st->st_nlink = 1;
    }
    return 0;
}
