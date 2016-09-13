project(fwGdcmIO VERSION 0.1)

find_package(Boost COMPONENTS filesystem REQUIRED)
find_package(GDCM REQUIRED)

include(${GDCM_USE_FILE})

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
    ${GDCM_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Boost_LIBRARIES}
    ${GDCM_LIBRARIES}
    gdcmCommon
    gdcmMSFF
    fwCore
    fwData
    fwMath
    fwMedData
    fwDataIO
    fwTools
    fwComEd
    fwRuntime
    fwDicomIOFilter
    fwLog
    fwJobs
    fwCom
    fwZip
    fwDicomTools
    fwDataTools
    fwServices
    fwDicomTools
)

add_target()

add_definitions(-D${PROJECT_NAME}_VERSION="${DASH_VERSION}")

