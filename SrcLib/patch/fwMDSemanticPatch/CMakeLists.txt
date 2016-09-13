project(fwMDSemanticPatch VERSION 0.1)

set(PRIVATE_LINKS
    fwAtoms
    fwAtomsPatch
    fwCore
    fwTools
    fwMedData
)

add_target()

add_definitions(-D${PROJECT_NAME}_VERSION="${DASH_VERSION}") #used to find xsd path