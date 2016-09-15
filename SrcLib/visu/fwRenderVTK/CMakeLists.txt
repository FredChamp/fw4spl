project(fwRenderVTK VERSION 0.1)

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
            vtkRenderingCore
            vtkRenderingAnnotation
            vtkRenderingFreeType
            vtkRenderingVolumeOpenGL2
        REQUIRED
        NO_MODULE)
    else()
        find_package(VTK COMPONENTS
            vtkInteractionWidgets
            vtkInteractionStyle
            vtkRenderingCore
            vtkRenderingAnnotation
            vtkRenderingFreeTypeOpenGL
            vtkRenderingVolumeOpenGL
        REQUIRED
        NO_MODULE)
    endif()
else()
    find_package(VTK COMPONENTS
            vtkRenderingOpenGL2
            vtkInteractionStyle
            vtkInteractionWidgets
            REQUIRED
            NO_MODULE)
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
    fwGui
    fwRender
    fwRuntime
    fwServices
    fwTools
    fwVtkIO
)

add_target()
