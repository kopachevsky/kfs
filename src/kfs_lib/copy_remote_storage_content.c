#include "copy_remote_storage_content.h"

int copy_mode(char *path) {
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    mode_t mode = sbuf.st_mode;
    return mode;
}

uid_t set_remote_storage_uid(char *path) {
    struct stat sbuf;
    int res = xglfs_getattr(path, &sbuf);
    if (res == -1) {
        printf("CANT READ UID  %s\n", strerror(errno));
    }
    return sbuf.st_uid;
}

gid_t set_remote_storage_gid(char *path) {
    struct stat sbuf;
    int res = xglfs_getattr(path, &sbuf);
    if (res == -1) {
        printf("CANT READ UID  %s\n", strerror(errno));
    }
    return sbuf.st_gid;
}

int remote_file_size(char *path) {
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    return  sbuf.st_size;
}

void copy_file(char *path) {
    log_debugf("copy_file start %s\n", path);
    char fpath[PATH_MAX_EXTENDED];
    char buf[remote_file_size(path)];
    fullpath(fpath, path);
    glfs_fd_t* remote_file_open = glfs_open(XGLFS_STATE->fs, path, O_RDONLY);
    if (unlikely(!remote_file_open)) {
        log_errorf("    Error open remote file %s\n", strerror( errno ));
    }
    int remote_file_read = glfs_pread(remote_file_open, buf, remote_file_size(path), 0, O_RDONLY);
    if (remote_file_read == -1) {
        log_errorf("    Error read remote file %s\n", strerror( errno ));
    }
    int local_file_open = open(fpath, O_CREAT | O_WRONLY | O_TRUNC, copy_mode(path));
    lchown(fpath, set_remote_storage_uid(path), set_remote_storage_gid(path));
    if (local_file_open == -1) {
        log_errorf("    Error create local file copy %s\n", strerror(errno));
    }
    int write_to_local_file = pwrite(local_file_open, buf, remote_file_size(path), 0);
    if (write_to_local_file == -1) {
        log_errorf("    Error write to local file copy %s\n", strerror(errno));
    }
    int remote_file_release = glfs_close(remote_file_open);
    if (remote_file_release == -1) {
        log_errorf("    Error release remote file %s\n", strerror(errno));
    }
    int local_file_release = close(local_file_open);
    if (local_file_release == -1) {
        log_errorf("    Error release local copy file %s\n", strerror(errno));
    }
    log_debugf("copy_file end");
}

void copy_directory(char *path, const int root) {
    log_debugf("copy_directory start %s\n", path);
    char fpath[PATH_MAX_EXTENDED];
    char new_path[PATH_MAX_EXTENDED];
    struct dirent *direntp;
    fullpath(fpath, path);
    int res = mkdir(fpath, copy_mode(path));
    lchown(fpath, set_remote_storage_uid(path), set_remote_storage_gid(path));
    if (res  == -1 ){
        log_errorf("    Erorr create local directory copy  %s\n", strerror( errno ));
    }
    set_default_user();
    glfs_fd_t* open_remote_directory = glfs_opendir(XGLFS_STATE->fs, path);
    if (unlikely(!open_remote_directory)) {
        log_errorf("    Error open remote directory %s\n", strerror( errno ));
    }
    while ((direntp = glfs_readdir(open_remote_directory)) != NULL) {
        fullpath(fpath, direntp->d_name);
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
            strcpy(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, direntp->d_name);
            if (direntp->d_type == DT_DIR) {
                copy_directory(new_path, root + 2);
            }
            if (direntp->d_type == DT_REG) {
                copy_file(new_path);
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
    struct stat sbuf;
    xglfs_getattr(path, &sbuf);
    glfs_fd_t* open_remote_storage = glfs_opendir(XGLFS_STATE->fs, path);
    if (unlikely(!open_remote_storage)) {
        log_errorf("    Error open remote storage %s\n", strerror( errno ));
    } else {
        while ((direntp = glfs_readdir(open_remote_storage)) != NULL) {
            fullpath(fpath, direntp->d_name);
            if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) {
                copy_content(direntp->d_type, direntp->d_name);
            }
        }
        int remote_storage_release = glfs_closedir(open_remote_storage);
        if (remote_storage_release == -1) {
            log_errorf("    Error release remote storage %s\n", strerror( errno ));
        }
    }
    log_debugf("read_remote_storage end");
    return 0;
}

int copy_remote_storage_content(){
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
