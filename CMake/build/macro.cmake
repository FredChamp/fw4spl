macro(add_target)
    # string( TOUPPER "${TYPE}" TYPE )
    set(DASH_VERSION ${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR})
    
    file(GLOB_RECURSE HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/* )
    file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/* )
    file(GLOB_RECURSE RCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} rc/* )
    
    if(TYPE STREQUAL "EXECUTABLE" )
        add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})
        
        set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bin)
        
        set_property(TARGET ${PROJECT_NAME} PROPERTY DEPENDENCIES ${PRIVATE_LINKS} ${PUBLIC_LINKS})
        set_property(TARGET ${PROJECT_NAME} PROPERTY F4S_TYPE ${TYPE})
        set_property(TARGET ${PROJECT_NAME} PROPERTY DASH_VERSION ${DASH_VERSION})
    
    elseif( TYPE STREQUAL "APP" )
        add_custom_target(${PROJECT_NAME}
            # COMMAND ${CMAKE_MAKE_PROGRAM} ${PRIVATE_LINKS}
            # WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
        add_dependencies(${PROJECT_NAME} ${PRIVATE_LINKS})
        
        
        # DEPENDS
        # Reference files and outputs of custom commands created with add_custom_command() command calls in the same directory (CMakeLists.txt file). They will be brought up to date when the target is built.
        #
        # Use the add_dependencies() command to add dependencies on other targets.
        #
        # SOURCES
        # Specify additional source files to be included in the custom target. Specified source files will be added to IDE project files for convenience in editing even if they have no build rules.
        set(RESSOURCES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bundles/${PROJECT_NAME}_${DASH_VERSION})
        
        set_property(TARGET ${PROJECT_NAME} PROPERTY DEPENDENCIES ${PRIVATE_LINKS} ${PUBLIC_LINKS})
        set_property(TARGET ${PROJECT_NAME} PROPERTY F4S_TYPE ${TYPE})
        set_property(TARGET ${PROJECT_NAME} PROPERTY DASH_VERSION ${DASH_VERSION})
        
        # Add each requirements to the activate list
        set(APP_DEPENDENCIES "")
        findRequirements(${PROJECT_NAME} APP_DEPENDENCIES)
        list(REMOVE_DUPLICATES APP_DEPENDENCIES)
        list(SORT APP_DEPENDENCIES)
        
        foreach(CURRENT_DEPENDENCY ${APP_DEPENDENCIES})
            get_property(DEPENDENCY_DASH_VERSION TARGET ${CURRENT_DEPENDENCY} PROPERTY DASH_VERSION)
            get_property(DEPENDENCY_START TARGET ${CURRENT_DEPENDENCY} PROPERTY START)
            # get the start option of the current requirement if exists
            if(${DEPENDENCY_START})
                list(APPEND START_BUNDLES "${CURRENT_DEPENDENCY}")
            endif()
                # check if a bundleParam macro had been use in the properties.cmake
                # if yes, get and set bundle param and values
            if(${CURRENT_DEPENDENCY}_PARAM_LIST)
                set(CURRENT_PARAM_LIST "${${CURRENT_DEPENDENCY}_PARAM_LIST}")
                set(CURRENT_PARAM_VALUES "${${CURRENT_DEPENDENCY}_PARAM_VALUES}")

                #set activate tag with parameters
                list(APPEND ACTIVATE_LIST "    <activate id=\"${CURRENT_DEPENDENCY}\" version=\"${DEPENDENCY_DASH_VERSION}\" >")
                foreach(CURRENT_PARAM ${CURRENT_PARAM_LIST})
                    list(FIND CURRENT_PARAM_LIST "${CURRENT_PARAM}" CURRENT_INDEX)
                    list(GET CURRENT_PARAM_VALUES "${CURRENT_INDEX}" CURRENT_VALUE)
                    list(APPEND ACTIVATE_LIST "        <param id=\"${CURRENT_PARAM}\" value=\"${CURRENT_VALUE}\" />")
                endforeach()

                list(APPEND ACTIVATE_LIST "    </activate>")
            # else simply set the activate tag
            else()
                 list(APPEND ACTIVATE_LIST "    <activate id=\"${CURRENT_DEPENDENCY}\" version=\"${DEPENDENCY_DASH_VERSION}\" />")
            endif()

        endforeach()
        string(REPLACE ";" "\n" ACTIVATE_LIST "${ACTIVATE_LIST}")
        
        if(START) # add a start for ctrl app
            list(APPEND START_BUNDLES "${PROJECT_NAME}")
        endif()
        
        if(START_BUNDLES)
            list(SORT START_BUNDLES)
            foreach(CURRENT_BUNDLES ${START_BUNDLES})
                set(START_BUNDLE_LIST "${START_BUNDLE_LIST}\n    <start id=\"${CURRENT_BUNDLES}\" />")
            endforeach()
        endif()

        if(NOT UNIQUE)
            set(UNIQUE false)
        endif()
        configure_file("${CMAKE_SOURCE_DIR}/CMake/build/profile.xml.in"    "${RESSOURCES_INSTALL_PATH}/profile.xml")
        
    else()
        if(SRCS)
            
            add_library(${PROJECT_NAME} ${HDRS} ${SRCS})
            
            # create the config.hpp for the current library
            string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPCASE)
            
            configure_file(
                "${CMAKE_SOURCE_DIR}/CMake/build/config.hpp.in"
                "${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME}/config.hpp"
                IMMEDIATE @ONLY)
            
            target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/include/")
        endif()
        
        if( TYPE STREQUAL "LIBRARY" )
            set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/lib)
            set(RESSOURCES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/share/${PROJECT_NAME}_${DASH_VERSION})
        elseif( TYPE STREQUAL "BUNDLE" )
            set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bundles/${PROJECT_NAME}_${DASH_VERSION})
            set(RESSOURCES_INSTALL_PATH ${LIBRARY_INSTALL_PATH})
            set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_${DASH_VERSION})
            if(START STREQUAL ON)
                set_target_properties(${PROJECT_NAME} PROPERTIES START ${START})
            endif()
        elseif( TYPE STREQUAL "TEST" )
        endif()
        
        #use set_property instead
        set_property(TARGET ${PROJECT_NAME} PROPERTY DEPENDENCIES ${PRIVATE_LINKS} ${PUBLIC_LINKS})
        set_property(TARGET ${PROJECT_NAME} PROPERTY F4S_TYPE ${TYPE})
        set_property(TARGET ${PROJECT_NAME} PROPERTY DASH_VERSION ${DASH_VERSION})
        
    endif()
    
    if(SRCS)
        # Include the projects in parameter and export them.
        # Compiling warnings will not be reported (because of SYSTEM).
        target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC ${PUBLIC_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR}/include)

        # Include the projects in parameter but do not export them.
        # Compiling warnings will not be reported (because of SYSTEM).
        target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${PRIVATE_INCLUDES})

        target_link_libraries(${PROJECT_NAME} PUBLIC ${PUBLIC_LINKS})
        target_link_libraries(${PROJECT_NAME} PRIVATE ${PRIVATE_LINKS})
        
        install(TARGETS ${PROJECT_NAME}
                DESTINATION ${LIBRARY_INSTALL_PATH}
        )
    endif()
    
    if(RCS)
        foreach(RESSOURCE_FILE ${RCS})
            
            get_filename_component(FILE_NAME ${RESSOURCE_FILE} NAME)
            if(NOT IS_DIRECTORY ${RESSOURCES_INSTALL_PATH})
                file(MAKE_DIRECTORY ${RESSOURCES_INSTALL_PATH})
            endif()
            configure_file(${RESSOURCE_FILE} ${RESSOURCES_INSTALL_PATH}/${NAME})
        endforeach()
    endif()
    

endmacro(add_target)

function(findRequirements TARGET_NAME)
    if(TARGET ${TARGET_NAME})
        get_property(PROJECT_TYPE TARGET ${TARGET_NAME} PROPERTY F4S_TYPE)
        if( PROJECT_TYPE STREQUAL "BUNDLE" OR PROJECT_TYPE STREQUAL "APP")
            list(APPEND APP_DEPENDENCIES  ${TARGET_NAME})
            
            get_property(DEPENDENCIES TARGET ${TARGET_NAME} PROPERTY DEPENDENCIES)
            foreach(DEPENDENCY ${DEPENDENCIES})
                    findRequirements(${DEPENDENCY})
            endforeach()
        endif()
    endif()
    set(APP_DEPENDENCIES ${APP_DEPENDENCIES} PARENT_SCOPE)
endfunction(findRequirements)

macro(bundleParam BUNDLE_NAME)
    set(options)
    set(oneValueArgs)
    set(multiValueArgs PARAM_VALUES PARAM_LIST)
    cmake_parse_arguments("${BUNDLE_NAME}" "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )
endmacro()