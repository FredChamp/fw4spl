macro(add_target)
    file(GLOB_RECURSE HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/* )
    file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/* )
    
    add_library(${PROJECT_NAME} ${HDRS} ${SRCS})

    # Include the projects in parameter and export them.
    # Compiling warnings will not be reported (because of SYSTEM).
    target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${PUBLIC_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/include)

    # Include the projects in parameter but do not export them.
    # Compiling warnings will not be reported (because of SYSTEM).
    target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${PRIVATE_INCLUDES})

    target_link_libraries(${PROJECT_NAME} PUBLIC ${PUBLIC_LINKS})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})

    get_property(dirs TARGET ${PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)
   message(STATUS "${PROJECT_NAME} include dirs='${dirs}'")

    
    # create the config.hpp for the current library
    string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPCASE)
    
    configure_file(
        "${CMAKE_SOURCE_DIR}/CMake/build/config.hpp.in"
        "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp"
        IMMEDIATE @ONLY)
    target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include/")
    
endmacro(add_target)