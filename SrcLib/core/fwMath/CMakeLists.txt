project(fwMath VERSION 0.1)

find_package(GLM REQUIRED)

set(PUBLIC_INCLUDES
    ${GLM_INCLUDE_DIR}
)

set(PRIVATE_LINKS
    fwCore
)

add_target()