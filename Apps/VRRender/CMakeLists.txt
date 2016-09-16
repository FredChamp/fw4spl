project(VRRender VERSION 0.9) 

set(PRIVATE_LINKS
    servicesReg
    dataReg

    gui
    guiQt

    activities
    appXml2
    memory
    ctrlMemory
    fwlauncher

    io
    ioAtoms
    ioITK
    ioVTK
    ioVtkGdcm
    ioData

    uiIO
    uiGenericQt
    uiMedDataQt

    2DVisualizationActivity
    3DVisualizationActivity
    volumeRenderingActivity
    blendActivity
    ioActivity

    dicomFilteringActivity
    dicomPacsReaderActivity
    dicomPacsWriterActivity

    media

    patchMedicalData

    filterVRRender

    preferences
)

bundleParam(appXml2 PARAM_LIST config parameters PARAM_VALUES VRRenderBase VRRenderAppBase)

add_target()
