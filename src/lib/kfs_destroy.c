#include "kfs_destroy.h"

void kfs_destroy (void *userdata) {
    return xglfs_destroy(userdata);
}
