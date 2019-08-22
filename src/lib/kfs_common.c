#include <kfs_common.h>

char *str_concat(const char* s1, const char* s2) {
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

int log(const char *msg) {
    LOG_CONFIG_PATH = "/home/donelkostino/kfs/tests/assets/zlog.conf";
    static int rc;
    if (!rc) {
        rc = dzlog_init(LOG_CONFIG_PATH, "default");
    }
    if (rc) {
        printf("init failed\n");
        return -1;
    }
    dzlog_info(msg);
    return 0;
}
