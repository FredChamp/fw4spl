project(fwLog VERSION 0.1)

find_package (Boost REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    fwCore
    fwData
    fwTools
)

add_target()
