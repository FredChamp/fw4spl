/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IODATA_MESHREADERSERVICE_HPP__
#define __IODATA_MESHREADERSERVICE_HPP__

#include <io/IReader.hpp>
#include <boost/filesystem/path.hpp>

#include "ioData/config.hpp"

namespace ioData
{
/**
 * @brief   Mesh reader service.
 * @class   MeshReaderService
 *
 * @date    2009.
 *
 * Service reading a trian file into a fwData::Mesh object.
 * @li This service has no specified start and stop method.
 * @li Use setConfiguration(cfg) and configure() methods to configure the mesh filename.
 * @li Use update() to read the mesh and notify observers.
 *
 * Service registered details : \n
 * fwServicesRegisterMacro( ::io::IReader , ::ioData::MeshReaderService , ::fwData::Mesh )
 */
class IODATA_CLASS_API MeshReaderService : public ::io::IReader
{

public:

    fwCoreServiceClassDefinitionsMacro ( (MeshReaderService)(::io::IReader) );

    /// Super class of reader services
    typedef ::io::IReader SuperClass;


    /** @name Specified reader service methods ( override from ::io::IReader )
     * @{
     */

    /**
     * @brief   returns  (filename) extension
     */
    IODATA_API virtual std::vector< std::string > getSupportedExtensions();

    /**
     * @brief Configure the mesh path.
     *
     * This method is used to find
     * the file path  using a file selector.
     */
    IODATA_API void configureWithIHM();
    /// @}

    /// Return path type managed by the service, here FILE
    IODATA_API virtual ::io::IOPathType getIOPathType() const;

protected:

    /** @name Service methods ( override from ::fwServices::IService )
     * @{
     */

    /**
     * @brief Starting method : default does nothing.
     *
     * This method is used to initialize the service.
     */
    virtual void starting() throw(::fwTools::Failed)
    {
    }

    /**
     * @brief Stopping method : default does nothing.
     *
     * The stopping method is empty for this service.
     */
    virtual void stopping() throw(::fwTools::Failed)
    {
    }


    /**
     * @brief Updating method. This method is called by update() from base service ( ::fwServices::IService )
     *
     * This method is used to update the service.
     * The mesh is read with the reader ::fwDataIO::reader::MeshReader.
     * Notify reading.
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

}

#endif /*__IODATA_MESHREADERSERVICE_HPP__*/
