#include "xglfs_chown.h"

int xglfs_chown(const char* _path, uid_t _owner, gid_t _group) {
    int ret = 0;

    ret = glfs_chown(XGLFS_STATE->fs, _path, _owner, _group);
    if (unlikely(ret < 0))
        ret = -errno;

    return ret;
}
