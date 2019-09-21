#include "xglfs_chown.h"

int xglfs_chown(const char* _path, uid_t _owner, gid_t _group) {
    int res = glfs_chown(XGLFS_STATE->fs, _path, _owner, _group);
    if (unlikely(res < 0)) {
        res = -errno;
    }
    return res;
}
