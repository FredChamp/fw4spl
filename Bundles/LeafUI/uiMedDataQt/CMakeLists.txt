project(uiMedDataQt VERSION 0.1)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Boost COMPONENTS regex REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}

    fwActivities
    fwCom
    fwComEd
    fwCore
    fwData
    fwDataCamp
    fwGui
    fwGuiQt
    fwMedData
    fwMedDataTools
    fwRuntime
    fwServices
    fwTools
    fwDataTools
    gui
    
    visuVTKQt
    visuVTKAdaptor
    uiImageQt
    ctrlSelection
)

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)


