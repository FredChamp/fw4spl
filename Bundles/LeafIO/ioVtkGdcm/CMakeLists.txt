project(ioVtkGdcm VERSION 0.1)

set(PRIVATE_LINKS
    fwCom
    fwComEd
    fwCore
    fwData
    fwGui
    fwMedData
    fwRuntime
    fwServices
    fwTools
    vtkGdcmIO
    io
    fwDataIO
)

add_target()
