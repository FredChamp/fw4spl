project(vtkCompositeMesh VERSION 0.1)

find_package(VTK COMPONENTS vtkInteractionWidgets REQUIRED NO_MODULE)

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    
    fwCom
    fwComEd
    fwData
    fwRender
    fwRenderVTK
    fwRuntime
    fwServices
    fwVtkIO
    fwGui
    fwTools
    fwCore
)

add_target()