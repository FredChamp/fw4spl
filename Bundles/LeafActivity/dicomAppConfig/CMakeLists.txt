project(dicomAppConfig VERSION 0.1)

set(PRIVATE_LINKS
    ctrlMemory
    ctrlSelection
    dataReg
    gui
    guiQt
    ioDicom
    ioGdcm
    servicesReg
    visuVTK
    visuVTKAdaptor
    visuVTKQt
)

add_target()
