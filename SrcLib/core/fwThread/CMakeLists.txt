cmake_minimum_required( VERSION 3.1 )

project(fwThread VERSION 0.1)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions(-DWIN32_LEAN_AND_MEAN)
endif()

set(PRIVATE_LINKS
    fwCore
)

add_target()
