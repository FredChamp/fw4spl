project(ioGdcm VERSION 0.1)

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
    fwCore
    fwData
    fwComEd
    fwTools
    fwRuntime
    fwMedData
    fwDataIO
    fwGdcmIO
    fwGui
    fwGuiQt
    fwLog
    fwJobs
    fwCom
    fwServices
    io
    
    dataReg
    ioDicom
    servicesReg
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
