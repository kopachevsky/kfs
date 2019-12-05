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
void copy_content(unsigned char type, char *path);

void copy_file(char *path) {
    log_debugf("copy_file start %s\n", path);
    char fpath[PATH_MAX_EXTENDED];
    char buf[BUFFERSIZE];
    fullpath(fpath, path);
    glfs_fd_t* remote_file_open = glfs_open(XGLFS_STATE->fs, path, O_RDONLY);
    if (unlikely(!remote_file_open)) {
        log_errorf("    Error open remote file %s\n", strerror( errno ));
    }
    int remote_file_read = glfs_pread(remote_file_open, buf, BUFFERSIZE, 0, O_RDONLY);
    if (remote_file_read == -1) {
        log_errorf("    Error read remote file %s\n", strerror( errno ));
    }
    int local_file_open = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, COPYMODE);
    if (local_file_open == -1) {
        log_errorf("    Error create local file copy %s\n", strerror( errno ));
    }
    int write_to_local_file = pwrite(local_file_open, buf, strlen(buf), 0);
    if (write_to_local_file == -1) {
        log_errorf("    Error write to local file copy %s\n", strerror( errno ));
    }
    int remote_file_release = glfs_close(remote_file_open);
    if (remote_file_release == -1) {
        log_errorf("    Error release remote file %s\n", strerror( errno ));
    }
    int local_file_release = close(local_file_open);
    if (local_file_release == -1) {
        log_errorf("    Error release local copy file %s\n", strerror( errno ));
    }
    log_debugf("copy_file end");
}

void copy_directory(char *path, const int root) {
    log_debugf("copy_directory start %s\n", path);
    char fpath[PATH_MAX_EXTENDED];
    char new_path[PATH_MAX_EXTENDED];
    struct dirent *direntp;
    fullpath(fpath, path);
    if ((mkdir(fpath, COPYMODE)) == -1) {
        log_errorf("    Erorr create local directory copy  %s\n", strerror( errno ));
    }
    glfs_fd_t* open_remote_directory = glfs_opendir(XGLFS_STATE->fs, path);
    if (unlikely(!open_remote_directory)) {
        log_errorf("    Error open remote directory %s\n", strerror( errno ));
    }
    while ((direntp = glfs_readdir(open_remote_directory)) != NULL) {
        fullpath(fpath, direntp->d_name);
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
            if (direntp->d_type == DT_DIR) {
                strcpy(new_path, path);
                strcat(new_path, "/");
                strcat(new_path, direntp->d_name);
                copy_directory(new_path, root + 2);;
            }
        }
    }
    int remote_directory_release = glfs_closedir(open_remote_directory);
    if (remote_directory_release == -1) {
        log_errorf("    Error release remote directory %s\n", strerror( errno ));
    }
    log_debugf("copy_directory end");
}


void copy_content(unsigned char type, char *path) {
    log_debugf("copy_files start %s\n", path);
    if (type == DT_REG) {
        copy_file(path);
    }
    if (type == DT_DIR) {
        copy_directory(path, 0);
    }
    log_debugf("copy_content end");
}

int read_remote_storage(char *path) {
    log_debugf("read_remote_storage start %s\n", path);
    char fpath[PATH_MAX_EXTENDED];
    struct dirent *direntp;
    struct fuse_file_info fi = read_struct(O_DIRECTORY);
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    if (xglfs_opendir(path, &fi) != 0) {
        log_errorf("    Error open remote storage %s\n", strerror( errno ));
    } else {
        while (likely((direntp = glfs_readdir(FH_TO_FD(XGLFS_STATE->g_fh))) != NULL)) {
            fullpath(fpath, direntp->d_name);
            if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
                copy_content(direntp->d_type, direntp->d_name);
            }
        }
        xglfs_releasedir(path, &fi);
    }
    log_debugf("read_remote_storage end");
    return 0;
}

int copy_remote_content(){
    log_debugf("copy_remote_content start");
    char *path = "/";
    int res = read_remote_storage(path);
    if (res == -1) {
        log_errorf("    Error reading remote torage %s\n", strerror( errno ));
        return -errno;
    }
    log_debugf("copy_remote_content end %d\n", res);
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
void fullpath(char fpath[PATH_MAX_EXTENDED], const char *path) {
    strcpy(fpath, XGLFS_STATE->cache);

    if (!str_ends_with_slash(fpath, PATH_JOIN_SEPERATOR)) {
        strncat(fpath, PATH_JOIN_SEPERATOR, strlen(PATH_JOIN_SEPERATOR)+1);
    }
    if (str_starts_with_slash(path, PATH_JOIN_SEPERATOR)) {
        char *filecopy = strdup(path);
        if (NULL == filecopy) {
            free(fpath);
        }
        strncat(fpath, ++filecopy, strlen(path)+1);
        free(--filecopy);
    } else {
        strncat(fpath, path, strlen(path)+1);
    }
}

void set_current_user() {
    struct fuse_context *cxt = fuse_get_context();
    setegid(cxt->gid);
    seteuid(cxt->uid);
    umask(cxt->umask);
}

void set_default_user() {
    setegid(0);
    seteuid(0);
    umask(0);
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
    log_debugf("    Umask of the calling process %d\n ", cxt->umask);
}
