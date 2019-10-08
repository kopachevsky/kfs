#include "xglfs_write.h"

int xglfs_write(const char* _path, const char* _buf, size_t _size, off_t _offset, struct fuse_file_info* _info) {
    (void)_path;
    int ret = 0;

    ret = glfs_pwrite(FH_TO_FD(XGLFS_STATE->g_fh), _buf, _size, _offset, 0);
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}

