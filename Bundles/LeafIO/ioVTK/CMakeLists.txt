project(ioVTK VERSION 0.1)

if(NOT ANDROID)
    find_package(VTK COMPONENTS vtkIOImport REQUIRED NO_MODULE)
endif()

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    fwComEd
    fwCore
    fwData
    fwDataIO
    fwGui
    fwMedData
    fwRuntime
    fwServices
    fwTools
    fwVtkIO
    fwCom
    fwThread
    fwJobs
    io
)

add_target()