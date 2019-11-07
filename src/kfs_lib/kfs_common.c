#include "kfs_common.h"

char *str_concat(const char *s1, const char *s2) {
    assert(s1 && s2);
    size_t s1len = strlen(s1);
    size_t s2len = strlen(s2);
    assert(s1len && s2len);
    char *path = malloc(s1len + s2len + 2);
    if (!path) return NULL;
    strcpy(path, s1);
    if ((path[s1len - 1] != '/') && (s2[0] != '/')) {
        strcat(path, "/");
    } else if (path[s1len - 1] == '/') {
        while (s2[0] == '/') s2++;
    }
    strcat(path, s2);
    return path;
}

struct fuse_file_info read_struct(int flag) {
    struct fuse_file_info s = {0};
    s.flags = flag;
    return  s;
}

void copy_content(char *path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    int in_fd, out_fd = 0, in_dir_fd, out_dir_fd;
    struct fuse_file_info fi = read_struct(O_RDONLY);
    struct fuse_file_info opendir = read_struct(O_DIRECTORY);
    struct stat sbuf;
    if ((xglfs_getattr(path, &sbuf)) == -1) {
        log_debugf("ERROR GETATTR %s\n", path);
    } else {
        log_debugf("GETATTR %s\n", path);
    }
    if ( (in_dir_fd = xglfs_opendir(path, &opendir)) != 0) {
        log_debugf("NOT A DIR %d\n", in_dir_fd);
        if ((in_fd = xglfs_open(path, &fi)) == -1) {
            log_debugf("Cannot open %d\n", in_fd);
        } else {
            if ((out_fd = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, COPYMODE) == -1)) {
                log_debugf("Cannot create %d\n", out_fd);
            }
            xglfs_release(path, &fi);
        }
    } else {
        if ((out_dir_fd = mkdir(fpath, COPYMODE)) == -1) {
            log_debugf("Cannot mkdir %d\n", out_dir_fd);
        } else {
            log_debugf("mkdir %d\n", fpath);
        }
        xglfs_releasedir(path, &opendir);
    }
}

int read_cluster() {
    char *path = "/";
    struct dirent *direntp;
    struct fuse_file_info fi = read_struct(O_DIRECTORY);
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    if (xglfs_opendir(path, &fi) != 0) {
        log_debugf("ERORR OPENDIR %s\n", path);
    } else {
        while (likely((direntp = glfs_readdir(FH_TO_FD(XGLFS_STATE->g_fh))) != NULL)) {
            copy_content(direntp->d_name);
        }
        xglfs_releasedir(path, &fi);
    }
    return 0;
}

void fullpath(char fpath[PATH_MAX], const char *path) {
    if (XGLFS_STATE == NULL) {
        strcpy(fpath, GLFS_DEFAULT_CACHE_DISK);
        strncat(fpath, path, PATH_MAX);
    } else {
        strcpy(fpath, XGLFS_STATE->cache);
        strncat(fpath, path, PATH_MAX);
    }
}

void set_current_user() {
    struct fuse_context *cxt = fuse_get_context();
    setegid(cxt->gid);
    seteuid(cxt->uid);
}

void set_default_user() {
    setegid(0);
    seteuid(0);
}

int log_init() {
    LOG_CONFIG_PATH = getenv("KFS_ZLOG_CONFIG");
    if (LOG_CONFIG_PATH == NULL) {
        // take default home
        char *homedir_path;
        if ((homedir_path = getenv("HOME")) == NULL) {
            homedir_path = getpwuid(getuid())->pw_dir;
        }
        LOG_CONFIG_PATH = str_concat(homedir_path, "zlog.conf");
    }
    int rc = dzlog_init(LOG_CONFIG_PATH,  "default");
    if (rc) {
        printf("zlog init failed for path %s\n", LOG_CONFIG_PATH);
        return -1;
    } else {
        printf("zlog init success for path %s\n", LOG_CONFIG_PATH);
        return 0;
    }
}

void log_info(const char *msg) {
    printf("%s\n", msg);
    dzlog_info("%s\n", msg);
}

void log_debug(const char *msg) {
    printf("%s\n", msg);
    dzlog_debug("%s\n", msg);
}

void log_error(const char *msg) {
    printf("%s\n", msg);
    dzlog_error("%s\n", msg);
    exit(1001);
}

void log_infof(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    char msg[2048];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_info("%s\n", msg);
    va_end(argp);
}

void log_debugf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    char msg[2048];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_debug("%s\n", msg);
    va_end(argp);
}

void log_errorf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    char msg[2048];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_error("%s\n", msg);
    va_end(argp);
//    exit(1001);
}
