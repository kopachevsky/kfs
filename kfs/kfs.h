#ifndef KFS_H
#define KFS_H

#define FUSE_USE_VERSION      26

//static const int128_t FIVE_GB = 5LL * 1024LL * 1024LL * 1024LL;

#include <fuse.h>

#define KFS_FUSE_EXIT() \
do{ \
  struct fuse_context* pcxt = fuse_get_context(); \
  if(pcxt){ \
    fuse_exit(pcxt->fuse); \
  } \
}while(0)

#ifdef KFS_MALLOC_TRIM
#ifdef HAVE_MALLOC_TRIM
#include <malloc.h>
#define KFS_MALLOCTRIM(pad)    malloc_trim(pad)
#else   // HAVE_MALLOC_TRIM
#define KFS_MALLOCTRIM(pad)
#endif  // HAVE_MALLOC_TRIM
#else   // KFS_MALLOC_TRIM
#define S3FS_MALLOCTRIM(pad)
#endif  // KFS_MALLOC_TRIM

#define KFS_XMLFREEDOC(doc) \
        do{ \
          xmlFreeDoc(doc); \
          KFS_MALLOCTRIM(0); \
        }while(0)
#define KFS_XMLFREE(ptr) \
        do{ \
          xmlFree(ptr); \
          KFS_MALLOCTRIM(0); \
        }while(0)
#define KFS_XMLXPATHFREECONTEXT(ctx) \
        do{ \
          xmlXPathFreeContext(ctx); \
          KFS_MALLOCTRIM(0); \
        }while(0)
#define KFS_XMLXPATHFREEOBJECT(obj) \
        do{ \
          xmlXPathFreeObject(obj); \
          KFS_MALLOCTRIM(0); \
        }while(0)

#endif // KFS_H
