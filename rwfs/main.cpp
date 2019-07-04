#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdlib.h>
#include <map>
#include <list>

#define GET_PARENT_DIR 1
#define GET_DIR 2
#define true 1

using namespace std;
//Todo create create separate classes for fileInfona and dirInfo
class fileInfo
{
public:
    string fileName;
    string fileContent;
    mode_t mode;
    time_t updateTime;

    fileInfo(string filename)
    {
        fileName = filename;
        fileContent = "";
        updateTime = time(NULL);
    }

    fileInfo(string filename, string content)
    {
        fileName = filename;
        fileContent = content;
        updateTime = time(NULL);
    }

    int length()
    {
        return fileContent.length();
    }
};

class dirInfo_t
{
public:
    string dirName;
    map<string, fileInfo*> fileList;
    dirInfo_t* parentDir;
    map<string, dirInfo_t*> childDir;
    map<string, time_t> fileTime;
    time_t createTime;

    dirInfo_t()
    {
        parentDir = NULL;
        dirName = "/";
    }

    int updateFileTime(string filename);
};

int dirInfo_t::updateFileTime(string filename)
{
    fileList[filename]->updateTime = time(NULL);
}

typedef map<string, fileInfo*>::iterator fileListIter;
typedef map<string, dirInfo_t*>::iterator dirListIter;

time_t rootCreateTime;
dirInfo_t* currentDirectory = NULL;
long curFsSize = 0;
long maxfsSize;


//////////////////////////////////////////////////////////

list<string> parsePath(string path)
{
    list<string> parsedPath;
    char* p;
    char* cPath = strdup(path.c_str());

    p = strtok(cPath, "/");

    while (p != NULL)
    {
        parsedPath.push_back(p);
        p = strtok(NULL, "/");
    }

    free(cPath);
    return parsedPath;
}

string getFileOrDirName(string path)
{
    list<string> pathList = parsePath(path);
    return pathList.back();
}

dirInfo_t* getDirectory(string path, int type)
{
    dirInfo_t* dInfo = currentDirectory;

    list<string> mylist = parsePath(path);
    if ((mylist.size() == 1) && (type == GET_PARENT_DIR))
    {
        return dInfo;
    }

    list<string>::iterator it = mylist.begin();
    int size = mylist.size();
    if (type == GET_PARENT_DIR)
        size--;

    for (int i = 0;i < size; it++,i++)
    {
        dirListIter iter = dInfo->childDir.find(*it);
        if (iter == dInfo->childDir.end())
            return NULL;

        dInfo = iter->second;
    }

    return dInfo;

}

int findFile(const char* path)
{
    dirInfo_t* dInfo = getDirectory(path, GET_PARENT_DIR);
    if (dInfo == NULL)
        return 0;

    string sPath = getFileOrDirName(path);
    fileListIter it = dInfo->fileList.begin();
    for (;it != dInfo->fileList.end(); it++)
    {
        if (!strcmp(sPath.c_str(), it->first.c_str()))
            return 1;
    }
    return 0;
}

static int rwsf_getattr(const char *path, struct stat *stbuf)
{
    int retValue = 0;

    memset(stbuf, 0, sizeof(struct stat));

    dirInfo_t* dInfo = NULL;
    dInfo = getDirectory(path, GET_DIR);//check whether its a dir

    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;  //should be 3 bec of hierarchical dir (. and ..)
        stbuf->st_mtime	= rootCreateTime;
        stbuf->st_size = 4096;
    }
    else if (dInfo != NULL)
    {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 3;  //should be 3 bec of hierarchical dir (. and ..)
        stbuf->st_mtime	= dInfo->createTime;
        stbuf->st_size = 4096;
    }
    else if (findFile(path) == true)
    {
        dInfo = getDirectory(path, GET_PARENT_DIR);
        if (dInfo == NULL)
            return -ENOENT;

        stbuf->st_mode = S_IFREG | 0755;
        stbuf->st_nlink = 1;
        string filename = getFileOrDirName(path);
        stbuf->st_size = dInfo->fileList[filename]->length();

        stbuf->st_mtime = dInfo->fileList[filename]->updateTime;
    }
    else
        retValue = -ENOENT;

    return retValue;
}

static int rwfs_opendir(const char * path, struct fuse_file_info *fileInfo)
{
    return 0;
}

int main(int argc, char *argv[])
{

}

