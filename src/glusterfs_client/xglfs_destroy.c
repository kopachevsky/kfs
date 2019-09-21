#include "xglfs_destroy.h"

void xglfs_destroy(void* _userdata) {
    (void) _userdata;
    glfs_fini(XGLFS_STATE->fs);

    free(XGLFS_STATE->protocol);
    free(XGLFS_STATE->server);
    free(XGLFS_STATE->volume);
    free(XGLFS_STATE->mountpoint);
    free(XGLFS_STATE->glfs_logfile);
    free(XGLFS_STATE->cache);

    struct xglfs_state* xglfs_state = XGLFS_STATE;
    free(xglfs_state);
}
