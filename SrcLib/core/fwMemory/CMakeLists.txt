project(fwMemory VERSION 0.1)

find_package (Boost COMPONENTS regex signals iostreams REQUIRED)

set(PRIVATE_LINKS
    ${Boost_LIBRARIES}
    fwCamp
    fwThread
    fwTools
)

set(PUBLIC_LINKS
    fwCom
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    #TODO write FindPsAPI ...
    target_link_libraries(${FWPROJECT_NAME} PRIVATE psapi)
endif()

add_target()