project(opVTKMesh VERSION 0.1)

find_package(VTK COMPONENTS vtkInteractionWidgets NO_MODULE)

set(PUBLIC_INCUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    
    fwMedData
    fwComEd
    fwCom
    fwData
    fwGui
    fwRuntime
    fwServices
    fwTools
    fwVtkIO
    fwCore
)

add_target()
