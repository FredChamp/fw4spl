project(fwCommand VERSION 0.1)

find_package(Boost COMPONENTS signals REQUIRED)

set(PRIVATE_LINKS
    ${Boost_SIGNALS_LIBRARY}
    fwComEd
    fwCom
    fwData
    fwServices
    fwTools
    fwCore
)

add_target()
