project(ioPacs VERSION 0.1)

find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(DCMTK REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

set(PRIVATE_INCLUDES
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${DCMTK_LIBRARIES}
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
    
    fwCore
    fwThread
    fwCom
    fwComEd
    fwGui
    fwGuiQt
    fwPacsIO
    fwRuntime
    fwTools
    fwData
    fwMedData
    fwServices
    gui
    io
    
    dataReg
    servicesReg
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)
