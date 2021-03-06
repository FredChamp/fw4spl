/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IODATA_TRANSFORMATIONMATRIX3DWRITERSERVICE_HPP__
#define __IODATA_TRANSFORMATIONMATRIX3DWRITERSERVICE_HPP__

#include <boost/filesystem/path.hpp>

#include <io/IWriter.hpp>

#include "ioData/config.hpp"

namespace ioData
{
/**
 * @brief   Transformation matrix 3D writer service.
 * @class   TransformationMatrix3DWriterService
 *
 * @date    2009.
 *
 * Service writing a TransformationMatrix3D object
 * @li Use setConfiguration(cfg) and configure() methods to configure the matrix filename.
 * @li Use start() to initialize the service.
 * @li Use update() to write the transformation matrix.
 * @li Use stop() to stop service before to destroy it.
 *
 * Service registered details : \n
 * fwServicesRegisterMacro( ::io::IWriter , ::ioData::TransformationMatrix3DWriterService , ::fwData::TransformationMatrix3D )
 */
class IODATA_CLASS_API TransformationMatrix3DWriterService : public ::io::IWriter
{

public:

    fwCoreServiceClassDefinitionsMacro ( (TransformationMatrix3DWriterService)(::io::IWriter) );

    /// Super class of writer services
    typedef ::io::IWriter SuperClass;


    /** @name Specified writer service methods ( override from ::io::IWriter )
     * @{
     */

    /**
     * @brief Configure the matrix path.
     *
     * This method is used to find
     * the file path  using a file selector.
     */
    IODATA_API virtual void configureWithIHM();

    /**
     * @brief   returns  (filename) extension
     */
    IODATA_API virtual std::vector< std::string > getSupportedExtensions();
    ///@}

    /// Return path type managed by the service, here FILE
    IODATA_API virtual ::io::IOPathType getIOPathType() const;

protected:

    /** @name Service methods ( override from ::fwServices::IService )
     * @{
     */

    /**
     * @brief Starting method. This method is called by start() from base service ( ::fwServices::IService )
     *
     * This method is used to initialize the service. The starting method is empty for this service.
     */
    IODATA_API virtual void starting( ) throw(::fwTools::Failed);

    /**
     * @brief Stopping method. This method is called by stop() from base service ( ::fwServices::IService )
     *
     * The stopping method is empty for this service.
     */
    IODATA_API virtual void stopping( ) throw(::fwTools::Failed);

    /**
     * @brief Updating method. This method is called by update() from base service ( ::fwServices::IService )
     *
     * This method is used to update the service.
     * The transformation matrix is written with the writer ::fwDataIO::writer::TransformationMatrix3DWriter.
     * Notify writing.
     */
    IODATA_API void updating() throw(::fwTools::Failed);

    /**
     * @brief Info method.
     *
     * This method is used to give
     * informations about the service.
     *
     * @param[out] _sstream output stream
     */
    IODATA_API virtual void info(std::ostream &_sstream );
    /// @}

};

} // namespace ioData

#endif // __IODATA_TRANSFORMATIONMATRIX3DWRITERSERVICE_HPP__
