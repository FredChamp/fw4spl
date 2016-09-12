project(fwAtomsPatch VERSION 0.1)

find_package(CAMP REQUIRED)
if(NOT ANDROID)
    find_package (Boost COMPONENTS log log_setup filesystem REQUIRED)
endif()

set(PUBLIC_INCLUDES
    ${CAMP_INCLUDE_DIR}
)

set(PRIVATE_LINKS
    fwAtomConversion
    fwAtoms
    fwCore
    fwTools
    fwRuntime
)
if(NOT ANDROID)
    list(APPEND PRIVATE_LINKS
        ${CAMP_LIBRARIES}
        ${Boost_LOG_LIBRARY}
        ${Boost_LOG_SETUP_LIBRARY}
        ${Boost_FILESYSTEM_LIBRARY}
    )
else()
    list(APPEND PRIVATE_LINKS
        ${CAMP_LIBRARIES}
        log
    )
endif()

add_target()