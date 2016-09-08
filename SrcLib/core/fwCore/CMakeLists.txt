project(fwCore VERSION 0.1)

if(ANDROID)
    find_package (Boost COMPONENTS thread system filesystem date_time chrono REQUIRED)
else()
    find_package (Boost COMPONENTS thread system filesystem date_time log log_setup REQUIRED)
endif()

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

set(PUBLIC_LINKS
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_DATE_TIME_LIBRARY}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_THREAD_LIBRARY}
)

# set(PRIVATE_INCLUDES ${})

if(ANDROID)
    set(PRIVATE_LINKS log)
else() 
    set(PRIVATE_LINKS
        ${Boost_LOG_LIBRARY}
        ${Boost_LOG_SETUP_LIBRARY}
    )
endif()

add_target()
