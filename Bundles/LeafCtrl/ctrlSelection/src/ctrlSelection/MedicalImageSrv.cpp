/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "ctrlSelection/MedicalImageSrv.hpp"

#include <fwCom/Signal.hxx>
#include <fwCom/Slots.hxx>

#include <fwComEd/fieldHelper/MedicalImageHelpers.hpp>
#include <fwComEd/helper/Image.hpp>

#include <fwData/Image.hpp>

#include <fwServices/macros.hpp>


namespace ctrlSelection
{

//-----------------------------------------------------------------------------

fwServicesRegisterMacro( ::fwServices::IController, ::ctrlSelection::MedicalImageSrv, ::fwData::Image );

//-----------------------------------------------------------------------------

MedicalImageSrv::MedicalImageSrv() throw()
{
}

//-----------------------------------------------------------------------------

MedicalImageSrv::~MedicalImageSrv() throw()
{
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::convertImage()
{
    ::fwData::Image::sptr pImg;

    if (this->isVersion2())
    {
        pImg = this->getInOut< ::fwData::Image >("image");
    }
    else
    {
        pImg = this->getObject< ::fwData::Image >();
    }
    if(::fwComEd::fieldHelper::MedicalImageHelpers::checkImageValidity(pImg))
    {
        ::fwComEd::helper::Image helper ( pImg );

        helper.createLandmarks();
        helper.createTransferFunctionPool();
        helper.createImageSliceIndex();

        auto sig = pImg->signal< ::fwData::Object::ModifiedSignalType >( ::fwData::Object::s_MODIFIED_SIG );
        ::fwCom::Connection::Blocker block(sig->getConnection(m_slotUpdate));
        helper.notify();
    }
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::starting()  throw ( ::fwTools::Failed )
{
    this->convertImage();
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::stopping()  throw ( ::fwTools::Failed )
{
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::swapping()  throw ( ::fwTools::Failed )
{
    this->convertImage();
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::configuring()  throw ( ::fwTools::Failed )
{
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::reconfiguring()  throw ( ::fwTools::Failed )
{
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::updating() throw ( ::fwTools::Failed )
{
    this->convertImage();
}

//-----------------------------------------------------------------------------

void MedicalImageSrv::info( std::ostream& _sstream )
{
}

//------------------------------------------------------------------------------

::fwServices::IService::KeyConnectionsType MedicalImageSrv::getObjSrvConnections() const
{
    KeyConnectionsType connections;
    connections.push_back( std::make_pair( ::fwData::Image::s_MODIFIED_SIG, s_UPDATE_SLOT ) );
    connections.push_back( std::make_pair( ::fwData::Image::s_BUFFER_MODIFIED_SIG, s_UPDATE_SLOT ) );

    return connections;
}

//-----------------------------------------------------------------------------

} // ctrlSelection
