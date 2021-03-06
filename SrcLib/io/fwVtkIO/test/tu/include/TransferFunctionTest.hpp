/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWVTKIO_UT_TRANSFERFUNCTIONTEST_HPP__
#define __FWVTKIO_UT_TRANSFERFUNCTIONTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

#include <fwData/TransferFunction.hpp>

namespace fwVtkIO
{
namespace ut
{

/**
 * @brief Test few methods to create transfer function for VTK.
 */
class TransferFunctionTest : public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( TransferFunctionTest );
CPPUNIT_TEST( toVtkLookupTableTest );
CPPUNIT_TEST( toBWVtkLookupTableTest );
CPPUNIT_TEST_SUITE_END();


public:
    // interface
    void setUp();
    void tearDown();

    void toVtkLookupTableTest();
    void toBWVtkLookupTableTest();

private:

    ::fwData::TransferFunction::sptr createTFColor();

};

} // end namespace ut
} // end namespace fwVtkIO

#endif //__FWVTKIO_UT_TRANSFERFUNCTIONTEST_HPP__
