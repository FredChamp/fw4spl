/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWATOMSBOOSTIO_UT_BOOSTIOTEST_HPP__
#define __FWATOMSBOOSTIO_UT_BOOSTIOTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

#include <fwZip/IWriteArchive.hpp>
#include <fwZip/IReadArchive.hpp>

#include <fwAtomsBoostIO/types.hpp>
#include <fwAtomsBoostIO/Writer.hpp>

namespace fwAtomsBoostIO
{
namespace ut
{

class BoostIOTest :  public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( BoostIOTest );
CPPUNIT_TEST( readWriteZipTest );
CPPUNIT_TEST( readWriteDirTest );
CPPUNIT_TEST_SUITE_END();

public:
    // interface
    void setUp();
    void tearDown();

    void readWriteZipTest();
    void readWriteDirTest();

protected:
    void readProcess(::fwZip::IReadArchive::sptr readArchive,
                     const ::boost::filesystem::path& rootFilename,
                     const ::fwAtomsBoostIO::FormatType& formatType = ::fwAtomsBoostIO::JSON);

    void writeProcess(::fwZip::IWriteArchive::sptr writeArchive,
                      const ::boost::filesystem::path& rootFilename,
                      ::fwAtomsBoostIO::FormatType format );
};


}  // namespace ut
}  // namespace fwAtomsBoostIO



#endif // __FWATOMSBOOSTIO_UT_BOOSTIOTEST_HPP__


