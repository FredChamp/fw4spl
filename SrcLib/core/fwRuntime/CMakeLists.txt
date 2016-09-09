project(fwRuntime VERSION 0.3)

find_package (Boost COMPONENTS regex REQUIRED)
find_package (LibXml2)
find_package (Iconv REQUIRED)

set(PUBLIC_INCLUDES
    ${LIBXML2_INCLUDE_DIR}
    ${ICONV_INCLUDE_DIR}
    )

set(PRIVATE_LINKS
    ${LIBXML2_LIBRARIES} 
    ${Boost_REGEX_LIBRARY}
    ${ICONV_LIBRARIES}
    fwCore
    )

add_target()

message(" dash " = ${DASH_VERSION})
add_definitions(-D${PROJECT_NAME}_VERSION="${DASH_VERSION}") #used to find xsd path
message(" dash2 " = ${DASH_VERSION})