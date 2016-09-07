cmake_minimum_required( VERSION 3.1 )

project(fwActivities VERSION 0.1)

find_package (Boost COMPONENTS regex REQUIRED)

set(PRIVATE_LINKS
    ${Boost_REGEX_LIBRARY}
)
set(PUBLIC_LINKS
    fwCore
    fwData
    fwDataCamp
    fwMath fwMedData
    fwRuntime
    fwTools
)

add_target()
