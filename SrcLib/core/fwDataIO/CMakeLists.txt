project(fwDataIO VERSION 0.2)

#racy compatibility
add_definitions(-DPRJ_NAME=\"${NAME}\")

find_package(ZLIB REQUIRED )

set(PRIVATE_INCLUDES
    ${ZLIB_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${ZLIB_LIBRARIES}
    fwComEd
    fwCore
    fwData
    fwDataTools
    fwTools
)

set(PUBLIC_LINKS
    fwJobs
)

add_target()

add_definitions(-D${PROJECT_NAME}_VERSION="${DASH_VERSION}") #used to find .dic path