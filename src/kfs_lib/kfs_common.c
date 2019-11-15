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

void copy_file(char *path) {
    char fpath[PATH_MAX];
    char buf[BUFFERSIZE];
    fullpath(fpath, path);
    int fd;
    struct fuse_file_info fi = read_struct(O_RDONLY);
    if ((xglfs_open(path, &fi)) == -1) {
        log_errorf("Error open remote file %s\n", strerror( errno ));
    } else {
        if ((fd = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, COPYMODE) == -1)) {
            log_errorf("Error create local copy %s\n", strerror( errno ));
        } else {
            if (xglfs_read(path, buf, BUFFERSIZE, 0, &fi) > 0) {
                close(fd);
                if ((open(fpath, O_WRONLY)) == -1) {
                    log_errorf("Error open local file %s\n", strerror( errno ));
                } else {
                    if ((pwrite(fd, buf, strlen(buf), 0)) == -1) {
                        log_errorf("Error write to local copy %s\n", strerror(errno));
                    }
                }
            } else {
                log_errorf("Error reading remote file %s\n", strerror(errno));
                }
        }
        xglfs_release(path, &fi);
    }
}

void copy_content(char *path) {
    char fpath[PATH_MAX];
    fullpath(fpath, path);
    struct fuse_file_info opendir = read_struct(O_DIRECTORY);
    struct stat sbuf;
    if ((xglfs_getattr(path, &sbuf)) == -1) {
        log_errorf("Error getattr %s\n", strerror( errno ));
    } else {
        if ((xglfs_opendir(path, &opendir)) != 0) {
            copy_file(path);
        } else {
            if ((mkdir(fpath, COPYMODE)) == -1) {
                log_errorf("Erorr create local dir cope  %s\n", strerror( errno ));
            }
            xglfs_releasedir(path, &opendir);
        }
    }
}

int read_cluster() {
    char *path = "/";
    struct dirent *direntp;
    struct fuse_file_info fi = read_struct(O_DIRECTORY);
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    if (xglfs_opendir(path, &fi) != 0) {
        log_errorf("Error opendir %s\n", strerror( errno ));
    } else {
        while (likely((direntp = glfs_readdir(FH_TO_FD(XGLFS_STATE->g_fh))) != NULL)) {
            copy_content(direntp->d_name);
        }
        xglfs_releasedir(path, &fi);
    }
    return 0;
}

bool str_ends_with_slash(const char *str, const char *end) {
    if (NULL == str || NULL == end) return false;
    unsigned long end_len = strlen(end);
    unsigned long str_len = strlen(str);
    return str_len < end_len ? false : !strcmp(str + str_len - end_len, end);
}
bool str_starts_with_slash(const char *str, const char *start) {
    for (; ; str++, start++)
        if (!*start)
            return true;
        else if (*str != *start)
            return false;
}
void fullpath(char fpath[MAX_PATH], const char *path) {
    strcpy(fpath, XGLFS_STATE->cache);
    unsigned long cache_size = strlen(fpath);
    if (!str_ends_with_slash(fpath, PATH_JOIN_SEPERATOR)) {
        strncat(fpath, PATH_JOIN_SEPERATOR, MAX_PATH + cache_size);
    }
    if (str_starts_with_slash(path, PATH_JOIN_SEPERATOR)) {
        char *filecopy = strdup(path);
        if (NULL == filecopy) {
            free(fpath);
        }
        strncat(fpath, ++filecopy, MAX_PATH + cache_size);
        free(--filecopy);
    } else {
        strncat(fpath, path, MAX_PATH + cache_size);
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
    char msg[PATH_MAX*10];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_info("%s\n", msg);
    va_end(argp);
}

void log_debugf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    char msg[PATH_MAX*10];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_debug("%s\n", msg);
    va_end(argp);
}

void log_errorf(const char *fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    char msg[PATH_MAX*10];
    vsprintf(msg, fmt, argp);
    printf("%s\n", msg);
    dzlog_error("%s\n", msg);
    va_end(argp);
//    exit(1001);
}

void fuse_context_log() {
    struct fuse_context *cxt = fuse_get_context();
    log_debugf("    User ID of the calling process %d\n ", cxt->uid);
    log_debugf("    Group ID of the calling process  %d\n ", cxt->gid);
    log_debugf("    Thread ID of the calling process %d\n ", cxt->pid);
    log_debugf("    Mask of the calling process %d\n ", cxt->umask);
}
