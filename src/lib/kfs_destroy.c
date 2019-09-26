#include "kfs_destroy.h"

void kfs_destroy (void *_userdata) {
    return xglfs_destroy(_userdata);
}
