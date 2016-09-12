project(fwComEd VERSION 0.1)

set(PRIVATE_LINKS
    fwData
    fwMedData
    fwRuntime
)

set(PUBLIC_LINKS
    fwMath
    fwServices
)
add_target()