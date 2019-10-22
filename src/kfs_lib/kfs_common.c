#include <pwd.h>
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

void fullpath(char fpath[MAX], const char *path) {
    if (XGLFS_STATE == NULL) {
        strcpy(fpath, GLFS_DEFAULT_CACHE_DISK);
        strncat(fpath, path, MAX);
    } else {
        strcpy(fpath, XGLFS_STATE->cache);
        strncat(fpath, path, MAX);
    }
}

int logger(const char *msg) {
    char *homedir_path;
    char *config_file_path = "/kfs/tests/assets/zlog.conf";
    if ((homedir_path = getenv("HOME")) == NULL) {
        homedir_path = getpwuid(getuid())->pw_dir;
    }
    char *fullpath = str_concat(homedir_path, config_file_path);
    LOG_CONFIG_PATH = fullpath;
    static int rc;
    if (!rc) {
        rc = dzlog_init(LOG_CONFIG_PATH,  "default");
    }
    if (rc) {
        printf("init failed\n");
        return -1;
    }
    dzlog_info("%s", msg);
    dzlog_error("%d", errno);
    return 0;
}
