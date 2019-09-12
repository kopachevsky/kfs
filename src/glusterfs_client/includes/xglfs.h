#ifndef KFS_XGLFS_H
#define KFS_XGLFS_H

#pragma once

#include <fuse.h>
#include <glusterfs/api/glfs.h>
#include <string.h>

#define GLFS_DEFAULT_PORT		24007
#define GLFS_DEFAULT_PROTOCOL	"tcp"
#define GLFS_DEFAULT_VERBOSITY	7
#define DEV_NULL				"/dev/null"
#define DEV_STDERR				"/dev/stderr"

#ifdef __GNUC__
#define likely(x)				__builtin_expect(!!(x), 1)
#define unlikely(x)				__builtin_expect(!!(x), 0)
#else /* __GNUC__ */
#define likely(x)				(x)
#define unlikely(x)				(x)
#endif /* __GNUC__ */

struct xglfs_state
{
    glfs_t* fs;
    char* protocol;
    char* server;
    int port;
    char* volume;
    char* mountpoint;
    char* glfs_logfile;
    int glfs_verbosity;
};

#define XGLFS_STATE	((struct xglfs_state*)fuse_get_context()->private_data)
#define FH_TO_FD(A)	((glfs_fd_t*)(uintptr_t)(A))
#define FD_TO_FH(A)	((uint64_t)(uintptr_t)(A))

#endif //KFS_XGLFS_H
