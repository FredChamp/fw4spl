project(uiGenericQt VERSION 0.1)

find_package(Qt5 COMPONENTS Core Gui Help Widgets REQUIRED)

set(PUBLIC_INCLUDES
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Help_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Help_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    
    fwCore
    fwData
    fwGui
    fwRuntime
    fwServices
    fwTools
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)


