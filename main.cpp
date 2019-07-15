#include "main.h"

static int kfs_getattr(const char* path, struct stat* stbuf) {
    string filename = path;
    string stripped_slash = strip_leading_slash(filename);
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));

    stbuf->st_uid = getuid();
    stbuf->st_gid = getgid();
    stbuf->st_atime = stbuf->st_mtime = stbuf->st_ctime = time(nullptr);

    if(filename == "/") {
        cout << "kfs_getattr("<<filename<<"): Returning attributes for /" << endl;
        stbuf->st_mode = S_IFDIR | 0777;
        stbuf->st_nlink = 2;

    } else if(file_exists(stripped_slash)) {
        cout << "kfs_getattr("<<stripped_slash<<"): Returning attributes" << endl;
        stbuf->st_mode = S_IFREG | 0777;
        stbuf->st_nlink = 1;
        stbuf->st_size = files[stripped_slash].size();

    } else {
        cout << "kfs_getattr("<<stripped_slash<<"): not found" << endl;
        res = -ENOENT;
    }

    return res;
}


static int kfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {

    if(strcmp(path, "/") != 0)	{
        cout << "kfs_readdir("<<path<<"): Only / allowed" << endl;
        return -ENOENT;
    }

    filler(buf, ".", nullptr, 0);
    filler(buf, "..", nullptr, 0);

    for (auto & file : files)
        filler(buf, file.first.c_str(), nullptr, 0);

    return 0;
}

static int kfs_open(const char* path, struct fuse_file_info* fi) {
    string filename = strip_leading_slash(path);

    if( !file_exists(filename) ) {
        cout << "kfs_readdir("<<filename<<"): Not found" << endl;
        return -ENOENT;
    }

    return 0;
}

static int kfs_read(const char* path, char* buf, size_t size, off_t offset,
                      struct fuse_file_info* fi) {
    string filename = strip_leading_slash(path);

    if( !file_exists(filename) ) {
        cout << "kfs_read("<<filename<<"): Not found" << endl;
        return -ENOENT;
    }

    FileContents &file = files[filename];
    size_t len = file.size();

    if (offset < len) {
        if (offset + size > len) {
            cout << "kfs_read("<<filename<<"): offset("<<offset<<
                 ") + size("<<size<<") > len("<<len<<"), setting to " << len - offset << endl;

            size = len - offset;
        }

        cout << "kfs_read("<<filename<<"): Reading "<< size << " bytes"<<endl;
        for(size_t i = 0; i < size; ++i)
            buf[i] = file[offset + i];

    } else {
        return -EINVAL;
    }

    return size;
}

int kfs_write(const char* path, const char* data, size_t size, off_t offset, struct fuse_file_info*) {
    string filename = strip_leading_slash(path);

    if( !file_exists(filename) ) {
        cout << "kfs_write("<<filename<<"): Not found" << endl;
        return -ENOENT;
    }

    cout << "kfs_write("<<filename<<"): Writing "<< size << " bytes startting with offset "<< offset<<endl;
    FileContents &file = files[filename];

    for(size_t i = 0; i < size; ++i)
        file[offset + i] = data[i];

    return size;
}

int kfs_unlink(const char *pathname) {
    files.erase( strip_leading_slash(pathname) );
    return 0;
}

int kfs_create(const char* path, mode_t mode, struct fuse_file_info *) {
    string filename = strip_leading_slash(path);

    if( file_exists(filename) ) {
        cout << "kfs_create("<<filename<<"): Already exists" << endl;
        return -EEXIST;
    }

    if( (mode & S_IFREG) == 0)	{
        cout << "kfs_create("<<filename<<"): Only files may be created" << endl;
        return -EINVAL;
    }

    cout << "kfs_create("<<filename<<"): Creating empty file" << endl;
    files[filename] = to_map("");
    return 0;
}



int kfs_fgetattr(const char* path, struct stat* stbuf, struct fuse_file_info *) {
    cout << "kfs_fgetattr("<<path<<"): Delegating to kfs_getattr" << endl;
    return kfs_getattr(path, stbuf);
}

int kfs_opendir(const char* path, struct fuse_file_info *) {
    cout << "kfs_opendir("<<path<<"): access granted" << endl;
    return 0;
}

int kfs_access(const char* path, int) {
    cout << "kfs_access("<<path<<") access granted" << endl;
    return 0;
}

int kfs_truncate(const char* path, off_t length) {
    string filename = strip_leading_slash(path);

    if( !file_exists(filename) ) {
        cout << "kfs_truncate("<<filename<<"): Not found" << endl;
        return -ENOENT;
    }

    FileContents &file = files[filename];

    if ( file.size() > length ) {
        cout << "kfs_truncate("<<filename<<"): Truncating current size ("<<file.size()<<") to ("<<length<<")" << endl;
        file.erase( file.find(length) , file.end() );

    } else if ( file.size() < length ) {
        cout << "kfs_truncate("<<filename<<"): Enlarging current size ("<<file.size()<<") to ("<<length<<")" << endl;

        for(int i = file.size(); i < length; ++i)
            file[i] = '\0';
    }

    return -EINVAL;
}

static struct fuse_operations kfs_oper;

int main(int argc, char** argv) {

    kfs_oper.getattr    = kfs_getattr;
    kfs_oper.readdir 	= kfs_readdir;
    kfs_oper.open   	= kfs_open;
    kfs_oper.read   	= kfs_read;
    kfs_oper.unlink 	= kfs_unlink;
    kfs_oper.write      = kfs_write;
    kfs_oper.truncate   = kfs_truncate;
    kfs_oper.opendir    = kfs_opendir;
    kfs_oper.access     = kfs_access;
    kfs_oper.create     = kfs_create;
    kfs_oper.fgetattr   = kfs_fgetattr;

    return fuse_main(argc, argv, &kfs_oper, nullptr);
}
