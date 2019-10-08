#include "xglfs_write.h"

int xglfs_write(const char* _path, const char* _buf, size_t _size, off_t _offset, struct fuse_file_info* _info) {
    (void)_path;
    printf("fd to write in gluster : %lu", FD_TO_FH(_info->fh));
    int ret = glfs_pwrite(FH_TO_FD(_info->fh), _buf, _size, _offset,_info->flags);
    if (unlikely(ret < 0)) {
        ret = -errno;
    }
    return ret;
}

