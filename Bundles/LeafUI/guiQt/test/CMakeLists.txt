
fwLoadProperties()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
find_package(CppUnit)

fwInclude(
    ${CPPUNIT_INCLUDE_DIR}
    ${Qt5Core_INCLUDE_DIRS}
    ${Qt5Gui_INCLUDE_DIRS}
    ${Qt5Widgets_INCLUDE_DIRS}
)

fwLink(
    ${CPPUNIT_LIBRARY}
    ${Qt5Core_LIBRARIES}
    ${Qt5Gui_LIBRARIES}
    ${Qt5Widgets_LIBRARIES}
)


