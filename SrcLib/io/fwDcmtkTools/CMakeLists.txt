project(fwDcmtkTools VERSION 0.1)

find_package(DCMTK REQUIRED)

set(PUBLIC_INCLDUDES
    ${DCMTK_config_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${DCMTK_LIBRARIES}
    fwCore
    fwTools
    fwComEd 
)

add_target()
