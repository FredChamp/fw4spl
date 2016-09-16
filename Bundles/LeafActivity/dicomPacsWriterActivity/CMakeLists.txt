project(dicomPacsWriterActivity VERSION 0.1)

set(PRIVATE_LINKS
    activities
    dicomAppConfig
    ctrlMemory
    ctrlSelection
    dataReg
    dicomPacsReaderActivity
    gui
    guiQt
    ioGdcm
    ioPacs
    media
    servicesReg
    visuVTK
    visuVTKAdaptor
    visuVTKQt
)

add_target()

