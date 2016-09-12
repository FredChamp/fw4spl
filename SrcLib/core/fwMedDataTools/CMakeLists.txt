project(fwMedDataTools VERSION 0.1)

find_package (Boost COMPONENTS date_time REQUIRED)
find_package(GDCM REQUIRED)

include(${GDCM_USE_FILE})

set(PRIVATE_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${GDCM_INCLUDE_DIRS}
    
)
set(PRIVATE_LINKS
    ${Boost_LIBRARIES}
    ${GDCM_LIBRARIES} gdcmMSFF
    fwCore
    fwCom
    fwData
    fwMedData
)

add_target()
