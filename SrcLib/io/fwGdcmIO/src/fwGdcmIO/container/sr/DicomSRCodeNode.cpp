/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwGdcmIO/container/sr/DicomSRCodeNode.hpp"
#include "fwGdcmIO/helper/DicomData.hpp"

#include <fwCore/spyLog.hpp>

#include <gdcmSequenceOfItems.h>
#include <gdcmUIDGenerator.h>

namespace fwGdcmIO
{
namespace container
{
namespace sr
{

//------------------------------------------------------------------------------

DicomSRCodeNode::DicomSRCodeNode(const DicomCodedAttribute& codedAttribute, const std::string& relationship
                                 , const DicomCodedAttribute& codedEntry) :
    ::fwGdcmIO::container::sr::DicomSRNode(codedAttribute, "CODE", relationship), m_codedEntry(codedEntry)
{
}

//------------------------------------------------------------------------------

DicomSRCodeNode::~DicomSRCodeNode()
{
}

//------------------------------------------------------------------------------

void DicomSRCodeNode::write(::gdcm::DataSet& dataset) const
{
    ::fwGdcmIO::container::sr::DicomSRNode::write(dataset);

    // Concept Code Sequence - Type 1
    ::gdcm::SmartPointer< ::gdcm::SequenceOfItems > codeSequence =
        this->createConceptNameCodeSequence(dataset, m_codedEntry);
    ::fwGdcmIO::helper::DicomData::insertSQ< 0x0040, 0xa168 >(codeSequence, dataset);
}

//------------------------------------------------------------------------------

void DicomSRCodeNode::print(std::ostream& os) const
{
    DicomSRNode::print(os);
    os << "\\nCoded entry : [" << m_codedEntry << "]";
}

//------------------------------------------------------------------------------

} //namespace sr
} //namespace container
} //namespace fwGdcmIO
