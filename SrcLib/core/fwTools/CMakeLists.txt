project(fwTools VERSION 0.1)

find_package (Boost COMPONENTS regex signals REQUIRED)

set(PUBLIC_LINKS
    ${Boost_LIBRARIES}
    fwCore
)

if(ANDROID)
    list(APPEND PRIVATE_LINKS
            fwRuntime
    )
endif()
    
add_target()
