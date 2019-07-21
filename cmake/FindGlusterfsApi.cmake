INCLUDE( FindPkgConfig )


PKG_SEARCH_MODULE(GLUSTERFS-API glusterfs-api)

if(NOT GLUSTERFS-API_FOUND EQUAL 1)
    message(SEND_ERROR "pkg-config for glusterfs-api is missing.")
endif(NOT GLUSTERFS-API_FOUND EQUAL 1)