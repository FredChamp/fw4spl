/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWGDCMIO_WRITER_TID_MEASUREMENTREPORT_HPP__
#define __FWGDCMIO_WRITER_TID_MEASUREMENTREPORT_HPP__

#include "fwGdcmIO/container/sr/DicomSRNode.hpp"
#include "fwGdcmIO/writer/tid/TemplateID.hpp"

#include <fwData/Image.hpp>

namespace fwGdcmIO
{
namespace writer
{
namespace tid
{

/**
 * @brief Measurement Report TID - This a root template
 * @see TID t1tt1 FIXME: Set the final TID
 */
class FWGDCMIO_CLASS_API MeasurementReport : public ::fwGdcmIO::writer::tid::TemplateID< ::fwData::Image >
{

public:
    /**
     * @brief Constructor
     * @param[in] writer GDCM writer that must be enriched
     * @param[in] instance DICOM instance used to share informations between modules
     * @param[in] image Image data
     */
    FWGDCMIO_API MeasurementReport(SPTR(::gdcm::Writer)writer,
                                   SPTR(::fwGdcmIO::container::DicomInstance)instance,
                                   ::fwData::Image::sptr image);

    /// Destructor
    FWGDCMIO_API virtual ~MeasurementReport();

    /**
     * @brief Create Measurement Report template root node
     * @param[in] useSCoord3D True if we must write SCOORD3D, false if we must write SCOORD
     */
    FWGDCMIO_API virtual SPTR(::fwGdcmIO::container::sr::DicomSRNode) createRootNode(bool useSCoord3D = true);


};

} // namespace tid
} // namespace writer
} // namespace fwGdcmIO

#endif /* __FWGDCMIO_WRITER_TID_MEASUREMENTREPORT_HPP__ */
