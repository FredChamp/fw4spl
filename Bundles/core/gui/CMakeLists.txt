project(gui VERSION 0.1)
 
find_package (Boost COMPONENTS regex REQUIRED)

set(PUBLIC_INCLUDES 
    ${Boost_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
    fwCom
    fwComEd
    fwCore
    fwData
    fwGui
    fwRuntime
    fwServices
    fwTools
    fwThread
    fwJobs
)

add_target()