/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IOVTK_SIMAGESERIESWRITER_HPP__
#define __IOVTK_SIMAGESERIESWRITER_HPP__

#include "ioVTK/config.hpp"

#include <io/IWriter.hpp>

#include <boost/filesystem/path.hpp>
#include <string>


namespace fwData
{
class Image;
}

namespace fwJobs
{
class IJob;
}


namespace ioVTK
{

/**
 * @brief   VTK Image Writer.
 *
 * Service writing an image series using the fwVtkIO lib.
 */
class IOVTK_CLASS_API SImageSeriesWriter : public ::io::IWriter
{

public:

    typedef ::fwCom::Signal< void ( SPTR(::fwJobs::IJob) ) > JobCreatedSignalType;

    /**
     * @brief Constructor. Do nothing.
     */
    IOVTK_API SImageSeriesWriter() throw();

    ~SImageSeriesWriter() throw()
    {
    }

    fwCoreServiceClassDefinitionsMacro ( (SImageSeriesWriter)( ::io::IWriter) );

    /**
     * @brief Configure the image path.
     */
    IOVTK_API virtual void configureWithIHM();

protected:

    IOVTK_API virtual ::io::IOPathType getIOPathType() const;

    /**
     * @brief Starting method.
     *
     * This method is used to initialize the service.
     */
    IOVTK_API virtual void starting() throw(::fwTools::Failed);

    /**
     * @brief Stopping method.
     *
     * The stopping method is empty for this service.
     */
    IOVTK_API virtual void stopping() throw(::fwTools::Failed);

    /**
     * @brief Updating method.
     *
     * This method is used to update the service.
     * The image is read.
     */
    IOVTK_API void updating() throw(::fwTools::Failed);

    /**
     * @brief Info method.
     *
     * This method is used to give informations about the service.
     */
    IOVTK_API void info(std::ostream &_sstream );


private:

    /**
     * @brief the m_bServiceIsConfigured value is \b true
     * if the image path is known.
     */
    bool m_bServiceIsConfigured;

    /**
     * @brief Image path.
     */
    ::boost::filesystem::path m_fsImgPath;

    SPTR(JobCreatedSignalType) m_sigJobCreated;

};

} // namespace ioVTK

#endif //__IOVTK_SIMAGESERIESWRITER_HPP__

