
cmake_minimum_required (VERSION 3.1)

project (fw4spl)

enable_testing()

include(CheckVariableExists)
include(CMakeParseArguments)
include(GetPrerequisites)

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/build/macro.cmake)

    # use, i.e. don't skip the full RPATH for the build tree
    SET(CMAKE_SKIP_BUILD_RPATH  FALSE)

    # when building, don't use the install RPATH already
    # (but later on when installing)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 

    SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

    # add the automatically determined parts of the RPATH
    # which point to directories outside the build tree to the install RPATH
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)


    # the RPATH to be used when installing, but only if it's not a system directory
    LIST(FIND CMAKE_PLATFORM_IMPLICIT_LINK_DIRECTORIES "${CMAKE_INSTALL_PREFIX}/lib" isSystemDir)
    IF("${isSystemDir}" STREQUAL "-1")
       SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
    ENDIF("${isSystemDir}" STREQUAL "-1")


set(BUILD_SHARED_LIBS ON)
if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to 'Debug' as none was specified.")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()
if(CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES ${CMAKE_BUILD_TYPE} CACHE STRING "List of supported configurations." FORCE)
endif()

#Use solution folders.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY AUTOGEN_TARGETS_FOLDER automoc)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")  #racy backward compatibility

if(UNIX AND NOT APPLE)
    option(DEBIAN_INSTALL "Install apps in a Debian-way" OFF)
endif()

if(DEBIAN_INSTALL)
    set(USE_SYSTEM_LIB CACHE BOOL ON)
else()
    option(USE_SYSTEM_LIB "Use system libraries to compile fw4spl" OFF)
    if(NOT USE_SYSTEM_LIB)
        set(EXTERNAL_LIBRARIES CACHE PATH "External libraries location")
    endif()
endif()


set(CREATE_SUBPROJECTS OFF CACHE BOOL "Create a project for each subproject")
set(BUILD_TESTS ON CACHE BOOL "Configures projects associated tests (<project>Test projects)")
set(ADDITIONAL_PROJECTS CACHE PATH
        "Paths to the additional projects"
    )

set(SET_API_VERSION ON)

if(ADDITIONAL_PROJECTS)
    foreach(ADDITIONAL_PROJECT ${ADDITIONAL_PROJECTS})
        # parse additional CMakeLists
        if(EXISTS ${ADDITIONAL_PROJECT}/CMakeLists.txt)
            get_filename_component(DIRECTORY_PATH ${ADDITIONAL_PROJECT} ABSOLUTE )
            get_filename_component(DIR_NAME ${DIRECTORY_PATH} NAME )
            add_subdirectory(${ADDITIONAL_PROJECT} ${DIR_NAME})
        endif()
    endforeach()
endif()

set(BUNDLE_PREFIX "Bundles")

# Set warning level and function export visibility on Unix
if(UNIX)
    if(APPLE)
        # actually the flag -fvisibility=hidden makes application crash on OSX
        set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wno-unused-parameter -Wno-ignored-qualifiers -fvisibility-ms-compat")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wno-unused-parameter -Wno-ignored-qualifiers -fvisibility-ms-compat")
        set(CMAKE_MACOSX_RPATH ON)
    else()
        set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} -Wall -Wextra -Wconversion -Wno-unused-parameter -Wno-ignored-qualifiers -fvisibility=hidden")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wconversion -Wno-unused-parameter -Wno-ignored-qualifiers -fvisibility=hidden")

        #To make a debian package we should install our bundle in /usr/share/...
        if(DEBIAN_INSTALL)
            set(BUNDLE_PREFIX "share/Bundles")
        endif()

    endif()
    # Color for ninja and Clang on Linux and OSX
    if (CMAKE_GENERATOR STREQUAL "Ninja")
        if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
            set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
        endif()
    endif()
endif()

# Building with all your cores on Visual Studio IDE
if(MSVC_IDE)
    set(CMAKE_C_FLAG "${CMAKE_C_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(LIBRARY_OUTPUT_DIR lib)

set(FWCMAKE_RESOURCE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake/)

if(CMAKE_SYSTEM_NAME MATCHES "Darwin")
    #http://stackoverflow.com/questions/6802903/c-ifdef-mac-os-x-question
    add_definitions(-D__MACOSX__) #racy backward compatibility
    set(LIBRARY_OUTPUT_DIR Libraries)
endif()


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${LIBRARY_OUTPUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${LIBRARY_OUTPUT_DIR})
# Fixed path for multi-config builds (e.g. msvc)
foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
    set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/bin )
    set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIR} )
    set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_BINARY_DIR}/${LIBRARY_OUTPUT_DIR} )
endforeach()

set(SPYLOG_LEVEL "error" CACHE STRING "Log level")
set(SPYLOG_LEVEL_VALUES "fatal;error;warning;info;debug;trace" CACHE INTERNAL
    "List of possible values for log level")
set(SPYLOG_LEVEL_MAP_fatal 1)
set(SPYLOG_LEVEL_MAP_error 2)
set(SPYLOG_LEVEL_MAP_warning 3)
set(SPYLOG_LEVEL_MAP_info 4)
set(SPYLOG_LEVEL_MAP_debug 5)
set(SPYLOG_LEVEL_MAP_trace 6)
set_property(CACHE SPYLOG_LEVEL PROPERTY STRINGS ${SPYLOG_LEVEL_VALUES} )
add_definitions(-DSPYLOG_LEVEL=${SPYLOG_LEVEL})

# require C++11 standard by default
if(ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++11")
else()
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()

if(ANDROID)
    add_definitions(-DBUNDLE_PREFIX="/data/data/com.fw4spl.${PROJECTS_TO_INSTALL}/${BUNDLE_PREFIX}")
else()
    add_definitions(-DBUNDLE_PREFIX="${BUNDLE_PREFIX}")
endif()

if(EXTERNAL_LIBRARIES)
    list(APPEND CMAKE_PREFIX_PATH ${EXTERNAL_LIBRARIES})
    list(APPEND CMAKE_MODULE_PATH ${EXTERNAL_LIBRARIES})
    list(APPEND CMAKE_FIND_ROOT_PATH ${EXTERNAL_LIBRARIES})

    file(GLOB LIB_CONFIGS ${EXTERNAL_LIBRARIES}/fw-*.cmake )
    foreach(LIB_CONFIG ${LIB_CONFIGS})
        message(STATUS "include : ${LIB_CONFIG}")
        include("${LIB_CONFIG}")
    endforeach()
elseif(USE_SYSTEM_LIB)
    list(APPEND CMAKE_PREFIX_PATH ${FWCMAKE_RESOURCE_PATH}/modules)
    list(APPEND CMAKE_MODULE_PATH ${FWCMAKE_RESOURCE_PATH}/modules)
    list(APPEND CMAKE_FIND_ROOT_PATH ${FWCMAKE_RESOURCE_PATH}/modules)
    file(GLOB LIB_CONFIGS ${FWCMAKE_RESOURCE_PATH}/modules/fw-*.cmake )
    foreach(LIB_CONFIG ${LIB_CONFIGS})
        message(STATUS "include : ${LIB_CONFIG}")
        include("${LIB_CONFIG}")
    endforeach()
endif()

add_subdirectory(fwlauncher)

add_subdirectory(SrcLib)

add_subdirectory(Bundles)

add_subdirectory(Samples)

add_subdirectory(Apps)