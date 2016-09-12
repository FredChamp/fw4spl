project(fwZip)

find_package( ZLIB REQUIRED )

# No forward, minizip should be private
set(PRIVATE_INCLUDES
    ${ZLIB_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${ZLIB_LIBRARIES}
    fwCore
)

add_target()