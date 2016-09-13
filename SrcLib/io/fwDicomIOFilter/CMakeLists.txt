project(fwDicomIOFilter VERSION 0.1)

find_package(DCMTK REQUIRED)

set(PUBLIC_INCLUDES
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${DCMTK_LIBRARIES}
    fwCore
    fwTools
    fwData
    fwMath
    fwMedData
    fwLog
)

add_target()