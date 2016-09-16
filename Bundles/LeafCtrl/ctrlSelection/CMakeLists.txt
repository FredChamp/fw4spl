project(ctrlSelection VERSION 0.1)

find_package(Boost COMPONENTS regex REQUIRED)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
    fwCom
    fwComEd
    fwCore
    fwData
    fwRuntime
    fwServices
    fwTools
    fwThread
)

add_target()


