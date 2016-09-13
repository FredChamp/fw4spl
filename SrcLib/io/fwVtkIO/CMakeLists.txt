project(fwVtkIO VERSION 0.1)

 if(NOT ANDROID) 
    find_package(VTK COMPONENTS
        vtkFiltersModeling
        vtkIOImage
        vtkIOLegacy
        vtkIOXML
        vtkFiltersGeometry
        vtkIOExport
        REQUIRED
        NO_MODULE)
 else()
    find_package(VTK COMPONENTS     
        vtkFiltersModeling
        vtkIOImage
        vtkIOLegacy
        vtkIOXML
        vtkFiltersGeometry
        vtkInteractionStyle
        vtkRenderingOpenGL2
        vtkRenderingFreeType
         REQUIRED
         NO_MODULE)
 endif()


include(${VTK_USE_FILE})

set(PUBLIC_INCLUDES
    ${VTK_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${VTK_LIBRARIES}
    fwComEd
    fwCore
    fwData
    fwDataIO
    fwMath
    fwMedData
    fwMemory
    fwTools
    fwJobs
)

add_target()