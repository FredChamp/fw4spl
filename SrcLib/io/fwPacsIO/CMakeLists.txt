project(fwPacsIO VERSION 0.1)

find_package(DCMTK REQUIRED)

set(PUBLIC_INCLUDES
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PUBLIC_LINKS
    ${DCMTK_LIBRARIES}
)
set(PRIVATE_LINKS
    fwCore
    fwTools
    fwThread
    fwData
    fwMedData
    fwCom
    fwDcmtkTools
)

add_target()