/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWVTKIO_UT_MESHTEST_HPP__
#define __FWVTKIO_UT_MESHTEST_HPP__

#include <cppunit/extensions/HelperMacros.h>

#include <fwData/Mesh.hpp>
#include <fwData/Array.hpp>

namespace fwVtkIO
{
namespace ut
{

/**
 * @brief Test many methods to create mesh.
 */
class MeshTest : public CPPUNIT_NS::TestFixture
{
CPPUNIT_TEST_SUITE( MeshTest );
CPPUNIT_TEST( testMeshToVtk );
CPPUNIT_TEST( testSyntheticMesh );
CPPUNIT_TEST( testExportImportSyntheticMesh );
CPPUNIT_TEST( testPointCloud );
CPPUNIT_TEST_SUITE_END();

public:
    // interface
    void setUp();
    void tearDown();

    void testMeshToVtk();
    void testSyntheticMesh();
    void testExportImportSyntheticMesh();
    void testPointCloud();

};

} // namespace ut
} // namespace fwVtkIO

#endif //__FWVTKIO_UT_MESHTEST_HPP__
