project(scene2D VERSION 0.1)

add_definitions("-DQT_NO_KEYWORDS")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PUBLIC_INCLUDES
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${LIBXML2_INCLUDE_DIR}
)

set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES} 
    ${Qt5Gui_LIBRARIES} 
    ${Qt5Widgets_LIBRARIES}
    
    fwComEd
    fwCore
    fwTools
    fwData
    fwGuiQt
    fwRender
    fwRuntime
    fwServices
    fwGui
    fwCom
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
