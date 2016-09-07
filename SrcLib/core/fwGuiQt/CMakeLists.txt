cmake_minimum_required( VERSION 3.1 )

project(fwGuiQt VERSION 0.1)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/bin/qt.conf" "${CMAKE_BINARY_DIR}/bin/qt.conf")

add_definitions("-DQT_NO_KEYWORDS")

find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)

set(PUBLIC_INCLUDES
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${Qt5Concurrent_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    ${Qt5Concurrent_LIBRARIES}
    fwCore
    fwData
    fwGui
    fwRuntime
    fwServices
    fwThread
    fwTools
)

if(ANDROID)
    list(APPEND PUBLIC_INCLUDES
        ${EXTERNAL_LIBRARIES}/include/QtGui/5.5.1/QtGui
    )
    
    list(APPEND PRIVATE_LINKS
        android
    )
endif()

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
