project(vtkGdcmIO VERSION 0.1)

find_package(VTK REQUIRED)
find_package(GDCM REQUIRED)

include(${GDCM_USE_FILE})

set(PUBLIC_INCLUDES
    ${GDCM_INCLUDE_DIRS}
)

set(PRIVATE_LINKS
    ${GDCM_LIBRARIES}

    vtkInteractionStyle
    vtkIOImage
    vtkCommonExecutionModel
    vtkCommonDataModel
    vtkCommonCore

    vtkgdcm
    gdcmMSFF
    gdcmDSED
    gdcmCommon
    
    fwCore
    fwData
    fwDataIO
    fwMedData
    fwMemory
    fwTools
    fwVtkIO
    fwJobs
)

add_target()