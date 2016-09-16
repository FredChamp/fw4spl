project(ioDicom VERSION 0.1)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PRIVATE_INCLUDES
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)


set(PRIVATE_LINKS
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    fwCom
    fwComEd
    fwCore
    fwDicomIOFilter
    fwDicomIOFilterQt
    fwGui
    fwGuiQt
    fwJobs
    fwLog
    fwRuntime
    fwServices
    fwTools
    gui
    io
    fwData
    fwMedData
    fwThread
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
