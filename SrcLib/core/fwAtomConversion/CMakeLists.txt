project(fwAtomConversion VERSION 0.1)

set(PRIVATE_LINKS
    fwAtoms
    fwCore
    fwData
    fwDataCamp
    fwMemory
    fwTools
)

set(PUBLIC_LINKS
    fwCamp
)

add_target()
