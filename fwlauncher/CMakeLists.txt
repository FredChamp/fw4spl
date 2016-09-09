project(fwlauncher VERSION 0.1)

set(TYPE EXECUTABLE)

find_package (Boost COMPONENTS program_options REQUIRED)

set(PRIVATE_LINKS
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    fwCore
    fwRuntime
)

add_target()

