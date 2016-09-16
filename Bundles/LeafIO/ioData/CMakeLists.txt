project(ioData VERSION 0.1)

find_package (Boost COMPONENTS regex REQUIRED)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
    fwComEd
    fwCom
    fwCore
    fwTools
    fwData
    fwDataIO
    fwDataTools
    fwGui
    fwRuntime
    fwServices
    io
)

add_target()
