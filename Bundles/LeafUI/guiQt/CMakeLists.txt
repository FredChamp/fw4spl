project(guiQt VERSION 0.1)

find_package(Boost COMPONENTS Regex REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)


set(PUBLIC_INCLUDES
    ${Boost_REGEX_INCLUDE_DIRS}
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
       fwComEd
       fwCom
       fwCore
       fwData
       fwDataCamp
       fwDataTools
       fwMedData
       fwGui
       fwGuiQt
       fwRuntime
       fwServices
       fwTools
       gui
)

# set( PLUGINS
#     platforms
#     imageformats
# )

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

