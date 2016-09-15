project(preferences VERSION 0.1)

set(PRIVATE_LINKS
    fwCore
    fwTools
    fwRuntime
    fwData
    fwDataCamp
    fwServices
    fwAtomsBoostIO
    fwAtomConversion
    fwZip
    fwAtoms
)

add_target()

add_definitions(-D${PROJECT_NAME}_VERSION="${DASH_VERSION}")