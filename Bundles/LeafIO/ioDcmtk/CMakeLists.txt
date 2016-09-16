project(ioDcmtk VERSION 0.1)

find_package(Boost COMPONENTS filesystem REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)
set(PRIVATE_LINKS
    fwCom
    fwComEd
    fwDcmtkIO
    fwGui
    fwCore
    fwData
    fwRuntime
    fwTools
    fwMedData
    fwServices
    io
)

add_target()
