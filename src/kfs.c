#include "kfs.h"

struct fuse_operations kfs_ops = {
                .init       = kfs_init,
                .getattr    = kfs_getattr,
                .fgetattr   = kfs_fgetattr,
                .access     = kfs_access,
                .open       = kfs_open,
                .read       = kfs_read,
                .write      = kfs_write,
                .truncate   = kfs_truncate,
                .release    = kfs_release,
                .readdir    = kfs_readdir,
                .unlink     = kfs_unlink,
                .rename     = kfs_rename,
                .mkdir      = kfs_mkdir,
                .rmdir      = kfs_rmdir,
                .create     = kfs_create,
                .mknod      = kfs_mknod,
                .chmod      = kfs_chmod,
                .link       = kfs_link,
                .symlink    = kfs_symlink,
                .ftruncate  = kfs_ftruncate,
                .readlink   = kfs_readlink,
                .fsync      = kfs_fsync,
                .opendir    = kfs_opendir,
                .releasedir = kfs_releasedir,
                .chown      = kfs_chown,
                .utimens    = kfs_utimens,
                .statfs     = kfs_statfs,
                .fallocate  = kfs_fallocate,
                .destroy    = kfs_destroy
};

int main(int argc, char** argv) {
    int options = 0;
    unsigned short int foreground = 0;
    char* invalid = NULL;
    struct option client_options[] = {
            { "protocol",	required_argument,	NULL,	't' },
            { "server",		required_argument,	NULL,	's' },
            { "port",		required_argument,	NULL,	'p' },
            { "volume",		required_argument,	NULL,	'l' },
            { "mountpoint",	required_argument,	NULL,	'm' },
            { "cache",	    required_argument,	NULL,	'c' },
            { "logfile",	    required_argument,	NULL,	'o' },
            { "verbosity",	required_argument,	NULL,	'v' },
            { "foreground",	no_argument,		NULL,	'f' },
            { "gluster_api", required_argument,	NULL,	'g' },
            { 0, 0, 0, 0}
    };
    if (getuid() != 0 || geteuid() != 0) {
        fprintf(stderr, "You must be root to mount kfs\n");
        exit(EX_NOPERM);
    }

    struct xglfs_state* xglfs_state = malloc(sizeof(struct xglfs_state));

    while ((options = getopt_long(argc, argv, "t:s:p:l:m:o:v:f", client_options, NULL)) != -1) {
        switch (options) {
            case 't':
                if (strcmp(optarg, "tcp") == 0 || strcmp(optarg, "udp") == 0) {
                    xglfs_state->protocol = strdup(optarg);
                } else {
                    exit(EX_USAGE);
                }
                break;
            case 's':
                xglfs_state->server = strdup(optarg);
                break;
            case 'p':
                xglfs_state->port = strtol(optarg, &invalid, 10);
                if (*invalid != '\0') {
                    exit(EX_USAGE);
                }
                break;
            case 'l':
                xglfs_state->volume = strdup(optarg);
                break;
            case 'm':
                xglfs_state->mountpoint = strdup(optarg);
                break;
            case 'c':
                xglfs_state->cache = strdup(optarg);
                break;
            case 'o':
                if (strcmp(optarg, "null") == 0) {
                    xglfs_state->glfs_logfile = strdup(DEV_NULL);
                } else if (strcmp(optarg, "stderr") == 0) {
                    xglfs_state->glfs_logfile = strdup(DEV_STDERR);
                } else {
                    xglfs_state->glfs_logfile = strdup(optarg);
                }
                break;
            case 'v':
                xglfs_state->glfs_verbosity = strtol(optarg, &invalid, 10);
                if (*invalid != '\0') {
                    exit(EX_USAGE);
                }
                break;
            case 'f':
                foreground = 1;
                break;
            case 'g':
                xglfs_state->gluster_api = strdup(optarg);
                break;
            default:
                exit(EX_USAGE);
        }
    }

    if (xglfs_state->server == 0) {
        fprintf(stderr, "%s\n", "To mount FS you need to specify server");
        exit(EX_USAGE);
    }
    if (xglfs_state->volume == 0) {
        fprintf(stderr, "%s\n", "To mount FS you need to specify volume");
        exit(EX_USAGE);
    }
    if (xglfs_state->mountpoint == 0) {
        xglfs_state->mountpoint = GLFS_DEFAULT_MOUNTPOINT;
    }
    if (xglfs_state->cache == 0) {
        xglfs_state->cache = GLFS_DEFAULT_CACHE_DISK;
    }
    if (!xglfs_state->protocol) {
        xglfs_state->protocol = strdup(GLFS_DEFAULT_PROTOCOL);
    }
    if (xglfs_state->port == 0) {
        xglfs_state->port = GLFS_DEFAULT_PORT;
    }
    if (!xglfs_state->glfs_logfile) {
        xglfs_state->glfs_logfile = strdup(DEV_NULL);
    }
    if (xglfs_state->glfs_verbosity == 0) {
        xglfs_state->glfs_verbosity = GLFS_DEFAULT_VERBOSITY;
    }

    char** args = calloc(foreground + 3, sizeof(char*));
    size_t index = 0;
    args[index++] = strdup(argv[0]);
    args[index++] = strdup("-orw,suid,dev,direct_io,allow_other,default_permissions");
    if (foreground) {
        args[index++] = strdup("-f");
    }
    args[index++] = xglfs_state->mountpoint;
    exit(fuse_main(index, args, &kfs_ops, xglfs_state));
}