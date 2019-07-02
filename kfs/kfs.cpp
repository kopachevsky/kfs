#include "kfs.h"

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Fuse interface functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

static int getattr (const char *, struct stat *, struct fuse_file_info *fi);
static int readlink (const char *, char *, size_t);
static int mknod (const char *, mode_t, dev_t);
static int mkdir (const char *, mode_t);
static int unlink (const char *);
static int rmdir (const char *);
static int symlink (const char *, const char *);
static int rename (const char *, const char *, unsigned int flags);
static int link (const char *, const char *);
static int chmod (const char *, mode_t, struct fuse_file_info *fi);
static int chown (const char *, uid_t, gid_t, struct fuse_file_info *fi);
static int truncate (const char *, off_t, struct fuse_file_info *fi);
static int open (const char *, struct fuse_file_info *);
static int read (const char *, char *, size_t, off_t, struct fuse_file_info *);
static int write (const char *, const char *, size_t, off_t, struct fuse_file_info *);
static int statfs (const char *, struct statvfs *);
static int flush (const char *, struct fuse_file_info *);
static int release (const char *, struct fuse_file_info *);
static int fsync (const char *, int, struct fuse_file_info *);
static int setxattr (const char *, const char *, const char *, size_t, int);
static int getxattr (const char *, const char *, char *, size_t);
static int listxattr (const char *, char *, size_t);
static int removexattr (const char *, const char *);
static int opendir (const char *, struct fuse_file_info *);
static int readdir (const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *, enum fuse_readdir_flags);
static int releasedir (const char *, struct fuse_file_info *);
static int fsyncdir (const char *, int, struct fuse_file_info *);
static void *init (struct fuse_conn_info *conn, struct fuse_config *cfg);
static void destroy (void *private_data);
static int access (const char *, int);
static int create (const char *, mode_t, struct fuse_file_info *);
static int lock (const char *, struct fuse_file_info *, int cmd, struct flock *);
static int utimens (const char *, const struct timespec tv[2], struct fuse_file_info *fi);
static int bmap (const char *, size_t blocksize, uint64_t *idx);
static int ioctl (const char *, unsigned int cmd, void *arg, struct fuse_file_info *, unsigned int flags, void *data);
static int poll (const char *, struct fuse_file_info *, struct fuse_pollhandle *ph, unsigned *reventsp);
static int write_buf (const char *, struct fuse_bufvec *buf, off_t off, struct fuse_file_info *);
static int read_buf (const char *, struct fuse_bufvec **bufp, size_t size, off_t off, struct fuse_file_info *);
static int flock (const char *, struct fuse_file_info *, int op);
static int fallocate (const char *, int, off_t, off_t, struct fuse_file_info *);
static ssize_t copy_file_range (const char *path_in, struct fuse_file_info *fi_in, off_t offset_in, const char *path_out, struct fuse_file_info *fi_out, off_t offset_out, size_t size, int flags);
static int getattr (const char *, struct stat *, struct fuse_file_info *fi);
static int readlink (const char *, char *, size_t);
static int mknod (const char *, mode_t, dev_t);
static int mkdir (const char *, mode_t);
static int unlink (const char *);
static int rmdir (const char *);
static int symlink (const char *, const char *);
static int rename (const char *, const char *, unsigned int flags);
static int link (const char *, const char *);
static int chmod (const char *, mode_t, struct fuse_file_info *fi);
static int chown (const char *, uid_t, gid_t, struct fuse_file_info *fi);
static int truncate (const char *, off_t, struct fuse_file_info *fi);
static int open (const char *, struct fuse_file_info *);
static int read (const char *, char *, size_t, off_t, struct fuse_file_info *);
static int write (const char *, const char *, size_t, off_t, struct fuse_file_info *);
static int statfs (const char *, struct statvfs *);
static int flush (const char *, struct fuse_file_info *);
static int release (const char *, struct fuse_file_info *);
static int fsync (const char *, int, struct fuse_file_info *);
static int setxattr (const char *, const char *, const char *, size_t, int);
static int getxattr (const char *, const char *, char *, size_t);
static int listxattr (const char *, char *, size_t);
static int removexattr (const char *, const char *);
static int opendir (const char *, struct fuse_file_info *);
static int readdir (const char *, void *, fuse_fill_dir_t, off_t, struct fuse_file_info *, enum fuse_readdir_flags);
static int releasedir (const char *, struct fuse_file_info *);
static int fsyncdir (const char *, int, struct fuse_file_info *);
static void *init (struct fuse_conn_info *conn, struct fuse_config *cfg);
static void destroy (void *private_data);
static int access (const char *, int);
static int create (const char *, mode_t, struct fuse_file_info *);
static int lock (const char *, struct fuse_file_info *, int cmd, struct flock *);
static int utimens (const char *, const struct timespec tv[2], struct fuse_file_info *fi);
static int bmap (const char *, size_t blocksize, uint64_t *idx);
static int ioctl (const char *, unsigned int cmd, void *arg, struct fuse_file_info *, unsigned int flags, void *data);
static int poll (const char *, struct fuse_file_info *, struct fuse_pollhandle *ph, unsigned *reventsp);
static int write_buf (const char *, struct fuse_bufvec *buf, off_t off, struct fuse_file_info *);
static int read_buf (const char *, struct fuse_bufvec **bufp, size_t size, off_t off, struct fuse_file_info *);
static int flock (const char *, struct fuse_file_info *, int op);
static int fallocate (const char *, int, off_t, off_t, struct fuse_file_info *);
static ssize_t copy_file_range (const char *path_in, struct fuse_file_info *fi_in, off_t offset_in, const char *path_out, struct fuse_file_info *fi_out, off_t offset_out, size_t size, int flags);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//  Functions
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
