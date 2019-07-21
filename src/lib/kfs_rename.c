

int kfs_rename(const char* from, const char* to) {
    int res = 0;
    res = rename(from, to);
    if(res == -1)
        return -errno;
    return 0;
}