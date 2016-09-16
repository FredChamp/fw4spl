project(ctrlCamp VERSION 0.1)

find_package(Boost COMPONENTS regex REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)

set(PUBLIC_LINKS
    ${Boost_REGEX_LIBRARY}
)

set(PRIVATE_LINKS
    fwCom
    fwCore
    fwTools
    fwRuntime
    fwComEd
    fwData
    fwMedData
    fwDataCamp
    fwServices
)

add_target()

