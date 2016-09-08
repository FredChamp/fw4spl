project(fwCamp VERSION 0.1)

find_package(CAMP REQUIRED)

set(PUBLIC_INCLUDES
    ${CAMP_INCLUDE_DIR}
)

set(PUBLIC_LINKS
    ${CAMP_LIBRARIES}
)

set(PRIVATE_LINKS
    fwCore
)

add_target()