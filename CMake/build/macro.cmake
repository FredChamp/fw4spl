macro(add_target)
    # string( TOUPPER "${TYPE}" TYPE )
    set(PROJECT_DASH_VERSION ${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR})
    
    file(GLOB_RECURSE HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} include/* )
    file(GLOB_RECURSE SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} src/* )
    file(GLOB_RECURSE RCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} rc/* )
    
    if(TYPE STREQUAL "EXECUTABLE" )
        add_executable(${PROJECT_NAME} ${HDRS} ${SRCS})
        
        set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bin)
    
    elseif( TYPE STREQUAL "APP" )
        add_custom_target(${PROJECT_NAME}
            COMMAND ${CMAKE_MAKE_PROGRAM} ${PRIVATE_LINKS}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
        set(RESSOURCES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bundles/${PROJECT_NAME}_${PROJECT_DASH_VERSION})
        
        # get_prerequisites(${PROJECT_NAME} DEPENDENCIES 1 0 "" "${CMAKE_INSTALL_PREFIX}") 
        # foreach(DEPENDENCY_TARGET ${PRIVATE_LINKS})
        #
        #   get_property(DEPS TARGET ${DEPENDENCY_TARGET} PROPERTY DEPENDENCIES)
        #  message("${DEPENDENCY_TARGET}_DEPS = ${DEPS}")
        # #   get_prerequisites($<TARGET_FILE:${DEPENDENCY_TARGET}> DEPENDENCIES 1 0 "" "${CMAKE_INSTALL_PREFIX}")
        # #   foreach(DEPENDENCY_FILE ${DEPENDENCIES})
        # #       message("DEPENDENCY_FILE=${DEPENDENCY_FILE}")
        # #   endforeach()
        # endforeach()
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
            set(RESSOURCES_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/share)
        elseif( TYPE STREQUAL "BUNDLE" )
            set(LIBRARY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/bundles/${PROJECT_NAME}_${PROJECT_DASH_VERSION})
            set(RESSOURCES_INSTALL_PATH ${LIBRARY_INSTALL_PATH})
        elseif( TYPE STREQUAL "TEST" )
        endif()
        
        if(RCS)
            install(FILES ${RCS}
                DESTINATION ${RESSOURCES_INSTALL_PATH}
            )
        endif()
        
    endif()
    

    set_property(TARGET ${PROJECT_NAME} PROPERTY DEPENDENCIES ${PRIVATE_LINKS} ${PUBLIC_LINKS})
    set_property(TARGET ${PROJECT_NAME} PROPERTY F4S_TYPE ${TYPE})
    
    if(TYPE STREQUAL "APP")
        # Add each requirements to the activate list
        set(APP_DEPENDENCIES "")
        findRequirements(${PROJECT_NAME} APP_DEPENDENCIES)
        message(" APP_DEPENDENCIES = ${APP_DEPENDENCIES}")
        # set_property(TARGET ${PROJECT_NAME} PROPERTY DEPENDENCIES ${APP_DEPENDENCIES})
        
        
        foreach(CURRENT_REQUIREMENT ${APP_DEPENDENCIES})

            # get the start option of the current requirement if exists
            if(${CURRENT_REQUIREMENT}_START)
                list(APPEND START_BUNDLES "${CURRENT_REQUIREMENT}")
            endif()

                # check if a bundleParam macro had been use in the properties.cmake
                # if yes, get and set bundle param and values
                # if(${PROJECT}_${CURRENT_REQUIREMENT}_PARAM_LIST)
                #     set(CURRENT_PARAM_LIST "${${PROJECT}_${CURRENT_REQUIREMENT}_PARAM_LIST}")
                #     set(CURRENT_PARAM_VALUES "${${PROJECT}_${CURRENT_REQUIREMENT}_PARAM_VALUES}")
                #
                #     #set activate tag with parameters
                #     list(APPEND ACTIVATE_LIST "    <activate id=\"${CURRENT_REQUIREMENT}\" version=\"${${CURRENT_REQUIREMENT}_DASH_VERSION}\" >")
                #     foreach(CURRENT_PARAM ${CURRENT_PARAM_LIST})
                #         list(FIND CURRENT_PARAM_LIST "${CURRENT_PARAM}" CURRENT_INDEX)
                #         list(GET CURRENT_PARAM_VALUES "${CURRENT_INDEX}" CURRENT_VALUE)
                #         list(APPEND ACTIVATE_LIST "        <param id=\"${CURRENT_PARAM}\" value=\"${CURRENT_VALUE}\" />")
                #     endforeach()
                #
                #     list(APPEND ACTIVATE_LIST "    </activate>")
                # # else simply set the activate tag
                # else()
                     list(APPEND ACTIVATE_LIST "    <activate id=\"${CURRENT_REQUIREMENT}\" version=\"${${CURRENT_REQUIREMENT}_DASH_VERSION}\" />")
                # endif()

        endforeach()
        string(REPLACE ";" "\n" ACTIVATE_LIST "${ACTIVATE_LIST}")

        # if(${PROJECT}_START) # add a start for ctrl app
        #     list(APPEND START_BUNDLES "${PROJECT}")
        # endif()

        # list(SORT START_BUNDLES)

        # foreach(CURRENT_BUNDLES ${START_BUNDLES})
        #     set(START_BUNDLE_LIST "${START_BUNDLE_LIST}\n    <start id=\"${CURRENT_BUNDLES}\" />")
        # endforeach()

        configure_file("${CMAKE_SOURCE_DIR}/CMake/build/profile.xml.in"    "${RESSOURCES_INSTALL_PATH}/profile.xml")
        
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