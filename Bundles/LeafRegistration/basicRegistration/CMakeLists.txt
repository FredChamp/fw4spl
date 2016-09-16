project(basicRegistration VERSION 0.1)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(ITK REQUIRED)
find_package(VTK COMPONENTS vtkCommonDataModel NO_MODULE REQUIRED)

set(PUBLIC_INCLUDES
    ${ITK_INCLUDE_DIRS}
    ${VTK_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}

    ITKCommon

    ${VTK_LIBRARIES}
    
    fwComEd
    fwDataTools
    fwGuiQt
    fwItkIO

    gui
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
