project(visuVTKAdaptor VERSION 0.1)

if(NOT ANDROID)
    # Just look one core module to get the version number
    find_package(VTK COMPONENTS
            vtkCommonCore
            REQUIRED
            NO_MODULE)
            
    if(${VTK_MAJOR_VERSION} STREQUAL "7")
        find_package(VTK COMPONENTS
            vtkInteractionWidgets
            vtkInteractionStyle
            vtkFiltersTexture
            vtkRenderingOpenGL2
            vtkIOLegacy
        REQUIRED
        NO_MODULE)
    else()
        find_package(VTK COMPONENTS
            vtkInteractionWidgets
            vtkInteractionStyle
            vtkFiltersTexture
            vtkRenderingOpenGL
            vtkIOLegacy
        REQUIRED
        NO_MODULE)
    endif()
else()

    find_package(VTK
        COMPONENTS
        vtkInteractionStyle
        vtkFiltersTexture
        vtkRenderingOpenGL2
        vtkIOLegacy
        REQUIRED
        NO_MODULE
    )
endif()

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    
    fwCom
    fwComEd
    fwCore
    fwData
    fwDataCamp
    fwGui
    fwMath
    fwMedData
    fwRenderVTK
    fwRuntime
    fwServices
    fwTools
    fwVtkIO
    
    dataReg
    servicesReg
    visuVTK
)

add_target()