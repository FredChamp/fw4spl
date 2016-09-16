project(visuVTKQt VERSION 0.1)

add_definitions("-DQT_NO_KEYWORDS")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(VTK COMPONENTS vtkViewsQt REQUIRED NO_MODULE)

set(PUBLIC_INCLUDES
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS} 
)

set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES} 
    ${Qt5Gui_LIBRARIES} 
    ${Qt5Widgets_LIBRARIES}
    ${VTK_LIBRARIES}
    
    fwCore
    fwData
    fwGui
    fwGuiQt
    fwRenderVTK
    fwRuntime
    fwServices
    fwTools
    fwCom
    
    visuVTK
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
