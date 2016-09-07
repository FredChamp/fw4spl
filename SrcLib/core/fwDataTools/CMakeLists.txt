cmake_minimum_required( VERSION 3.1 )

project(fwDataTools VERSION 0.1)

find_package(GLM REQUIRED)

set(PUBLIC_INCLUDES
    ${GLM_INCLUDE_DIR}
)

set(PRIVATE_LINKS
    fwComEd
    fwData
    fwMath
)

add_target()
