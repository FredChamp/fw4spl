project(fwItkIO VERSION 0.1)

find_package(ITK REQUIRED)
find_package(JPEG REQUIRED)
find_package(ZLIB REQUIRED )

find_library(VGL_ALGO_LIBRARY   vgl_algo )
find_library(VNL_ALGO_LIBRARY   vnl_algo )
find_library(VNL_LIBRARY        vnl )
find_library(VCL_LIBRARY        vcl )
find_library(V3P_NETLIB_LIBRARY v3p_netlib )
find_library(JPEG_LIBRARY libjpeg)
find_path(VNL_INCLUDE_PATH  vxl/core/vnl/vnl_alloc.h)

set(PUBLIC_INCLUDES
    ${ITK_INCLUDE_DIRS}
    ${VNL_INCLUDE_PATH}
    ${VNL_INCLUDE_PATH}/vxl
    ${VNL_INCLUDE_PATH}/vxl/core
    ${VNL_INCLUDE_PATH}/vxl/vcl
)

set(PRIVATE_INCLUDES
    ${ZLIB_INCLUDE_DIRS}
)

# Since ITK is template-based, this make sense to force the link for dependencies
set(PUBLIC_LINKS
    ${VNL_LIBRARY}
    ${VNL_ALGO_LIBRARY}
    ${VCL_LIBRARY}
    ${VGL_ALGO_LIBRARY}
    ${V3P_NETLIB_LIBRARY}

    ITKCommon
    ITKIOImageBase
    ITKIOJPEG
    ITKMetaIO
    itksys
    itkopenjpeg
)


set(PRIVATE_LINKS
    ${ZLIB_LIBRARIES}
    ${JPEG_LIBRARY}
    fwComEd
    fwCore
    fwData
    fwDataIO
    fwTools
)

add_target()