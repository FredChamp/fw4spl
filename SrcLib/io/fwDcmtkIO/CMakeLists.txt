project(fwDcmtkIO VERSION 0.1)

find_package(Boost COMPONENTS filesystem regex REQUIRED)
find_package(DCMTK REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PUBLIC_LINKS
    fwDataIO
)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
    ${DCMTK_LIBRARIES}
    fwCore
    fwTools
    fwData
    fwThread
    fwMedData
    fwCom
    fwComEd
    fwZip
    fwDicomIOFilter
    fwDicomTools
    fwDcmtkTools
    fwMemory
    fwLog
)

add_target()