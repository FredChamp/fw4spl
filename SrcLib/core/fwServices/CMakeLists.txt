project(fwServices VERSION 0.1)

find_package(Boost COMPONENTS regex REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)
set(PUBLIC_LINKS
    ${Boost_REGEX_LIBRARY}
    fwActivities
    fwCom
    fwDataCamp
    fwRuntime
)

add_target()
