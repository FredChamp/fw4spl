project(fwDicomIOFilterQt VERSION 0.1)

find_package (Boost REQUIRED)
find_package(DCMTK REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets Concurrent REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
     ${DCMTK_LIBRARIES}
     ${Qt5Core_LIBRARIES}
     ${Qt5Gui_LIBRARIES}
     ${Qt5Widgets_LIBRARIES}
     ${Qt5Concurrent_LIBRARIES}
     fwCore
     fwTools
     fwMedData
     fwDicomIOFilter
     fwGui
     fwGuiQt
     fwDcmtkTools
 )

add_target()

set_target_properties(${PROJECT_NAME} PROPERTIES AUTOMOC TRUE)

