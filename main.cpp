#include "main.h"

typedef map<int, unsigned char> FileContents;
typedef map<string, FileContents> FileMap;
static FileMap files;

static bool file_exists(string filename) {
    bool b = files.find(filename) != files.end();
    cout << "file_exists: " << filename << ": " << b << endl;
    return b;
}

FileContents to_map(string data) {
    FileContents data_map;
    int i = 0;

    for (string::iterator it = data.begin(); it < data.end(); ++it)
        data_map[i++] = *it;

    return data_map;
}

static string strip_leading_slash(string filename) {
    bool starts_with_slash = false;

    if( filename.size() > 0 )
        if( filename[0] == '/' )
            starts_with_slash = true;

    return starts_with_slash ? filename.substr(1, string::npos) : filename;
}

static int kfs_getattr(const char* path, struct stat* stbuf) {
    string filename = path;
    string stripped_slash = strip_leading_slash(filename);
    int res = 0;
    memset(stbuf, 0, sizeof(struct stat));

    stbuf->st_uid = getuid();
    stbuf->st_gid = getgid();
    stbuf->st_atime = stbuf->st_mtime = stbuf->st_ctime = time(NULL);

    if(filename == "/") { //Attribute des Wurzelverzeichnisses
        cout << "kfs_getattr("<<filename<<"): Returning attributes for /" << endl;
        stbuf->st_mode = S_IFDIR | 0777;
        stbuf->st_nlink = 2;

    } else if(file_exists(stripped_slash)) { //Eine existierende Datei wird gelesen
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

int kfs_fgetattr(const char* path, struct stat* stbuf, struct fuse_file_info *) {
    cout << "kfs_fgetattr("<<path<<"): Delegating to kfs_getattr" << endl;
    return kfs_getattr(path, stbuf);
}
static struct fuse_operations kfs_oper;

int main(int argc, char** argv) {

    kfs_oper.getattr	= kfs_getattr;
    kfs_oper.fgetattr = kfs_fgetattr;

    return fuse_main(argc, argv, &kfs_oper, NULL);
}

}