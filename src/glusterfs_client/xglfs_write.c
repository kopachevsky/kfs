#include "xglfs_write.h"

int xglfs_write(const char* _path, const char* _buf, size_t _size, off_t _offset, struct fuse_file_info* _info) {
    (void)_path;
    int res = glfs_pwrite(FH_TO_FD(_info->fh), _buf, _size, _offset,_info->flags,NULL, NULL);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return res;
}

