fwLoadProperties()
find_package(CppUnit)

find_package(VTK COMPONENTS
    vtkIOLegacy
    vtkFiltersSources
    vtkCommonExecutionModel
    vtkCommonDataModel
    vtkCommonCore
    REQUIRED
    NO_MODULE )

fwForwardInclude(
    ${CPPUNIT_INCLUDE_DIR}
    ${VTK_INCLUDE_DIRS}
)

fwLink(
    ${CPPUNIT_LIBRARY}
    ${VTK_LIBRARIES}
)
