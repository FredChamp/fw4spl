project(visuVTKVRAdaptor VERSION 0.1)

# Just look one core module to get the version number
find_package(VTK COMPONENTS
        vtkCommonCore
        REQUIRED
        NO_MODULE)
        
if(${VTK_MAJOR_VERSION} STREQUAL "7")
    find_package(VTK COMPONENTS
        vtkInteractionWidgets
        vtkRenderingVolumeOpenGL2
        vtkRenderingCore
        vtkIOImage
        vtkCommonDataModel
        vtkCommonCore
    REQUIRED
    NO_MODULE)
else()
    find_package(VTK COMPONENTS
        vtkInteractionWidgets
        vtkRenderingVolumeOpenGL
        vtkRenderingCore
        vtkIOImage
        vtkCommonDataModel
        vtkCommonCore
    REQUIRED
    NO_MODULE)
endif()

include(${VTK_USE_FILE})

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES} 
    
    fwCom
    fwComEd
    fwData
    fwRenderVTK
    fwRuntime
    fwServices
    fwVtkIO
    fwTools
    fwCore
)

add_target()