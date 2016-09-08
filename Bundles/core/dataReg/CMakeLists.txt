project(dataReg VERSION 0.1)

find_package (Boost COMPONENTS thread system filesystem REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)
set(PRIVATE_LINKS
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    fwCore 
    fwRuntime
    fwServices
)

add_target()