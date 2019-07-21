INCLUDE( FindPkgConfig )


PKG_SEARCH_MODULE(FUSE fuse)

if(NOT FUSE_FOUND EQUAL 1)
    message(SEND_ERROR "pkg-config for fuse is missing.")
endif(NOT FUSE_FOUND EQUAL 1)