/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWATOMSBOOSTIO_READER_HPP__
#define __FWATOMSBOOSTIO_READER_HPP__

#include <boost/filesystem/path.hpp>

#include <fwCore/macros.hpp>

#include "fwAtomsBoostIO/types.hpp"
#include "fwAtomsBoostIO/config.hpp"

namespace fwAtoms
{
class Base;
}
namespace fwZip
{
class IReadArchive;
}

namespace fwAtomsBoostIO
{

class FWATOMSBOOSTIO_CLASS_API Reader
{

public:

    FWATOMSBOOSTIO_API SPTR(::fwAtoms::Base) read( const SPTR(::fwZip::IReadArchive)& archive,
                                                   const ::boost::filesystem::path& rootFilename = "root.json",
                                                   FormatType format = JSON ) const;

protected:

    SPTR(::fwAtoms::Base) m_atom;

};

}

#endif /* __FWATOMSBOOSTIO_READER_HPP__ */

