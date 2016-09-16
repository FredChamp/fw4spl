project(patchMedicalData VERSION 0.1)

find_package(Boost COMPONENTS system REQUIRED)

set(PUBLIC_INCLUDES
    ${Boost_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${Boost_SYSTEM_LIBRARY}
    fwMDSemanticPatch
    fwRuntime
    fwStructuralPatch
    fwAtoms
)

add_target()
