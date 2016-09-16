project(volumeRenderingActivity VERSION 0.1)

set(PRIVATE_LINKS
    2DVisualizationActivity
    3DVisualizationActivity
    gui
    guiQt
    ctrlSelection
    uiVisu
    uiVisuQt
    visuVTKAdaptor
    visuVTKVRAdaptor
    uiImageQt
    scene2D
    uiTF
    uiIO
    media
)

add_target()