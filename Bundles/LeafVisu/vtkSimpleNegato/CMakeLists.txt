project(vtkSimpleNegato VERSION 0.1)

find_package(VTK COMPONENTS vtkInteractionWidgets REQUIRED NO_MODULE)

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    
    fwCom
    fwCore
    fwTools
    fwComEd
    fwData
    fwRender
    fwRenderVTK
    fwRuntime
    fwServices
    fwVtkIO
    fwGui
)

add_target()
