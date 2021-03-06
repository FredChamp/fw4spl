/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "gui/action/SSlotCaller.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slot.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwCore/base.hpp>

#include <fwGui/dialog/MessageDialog.hpp>

#include <fwRuntime/Extension.hpp>
#include <fwRuntime/helper.hpp>

#include <fwServices/macros.hpp>

#include <fwTools/fwID.hpp>

#include <boost/regex.hpp>

namespace gui
{
namespace action
{

fwServicesRegisterMacro( ::fwGui::IActionSrv, ::gui::action::SSlotCaller, ::fwData::Object );

//-----------------------------------------------------------------------------

SSlotCaller::SSlotCaller() throw()
{
}

//-----------------------------------------------------------------------------

SSlotCaller::~SSlotCaller() throw()
{
}

//-----------------------------------------------------------------------------

void SSlotCaller::starting() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();
    this->actionServiceStarting();
}

//-----------------------------------------------------------------------------

void SSlotCaller::stopping() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    this->actionServiceStopping();
}

//-----------------------------------------------------------------------------

void SSlotCaller::info(std::ostream &_sstream )
{
    _sstream << "Starter Action" << std::endl;
}

//-----------------------------------------------------------------------------

void SSlotCaller::updating() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    for(SlotInfoType info :  m_slotInfos)
    {
        HasSlotIDType HasSlotId = info.first;
        ::fwCom::Slots::SlotKeyType slotKey = info.second;

        if (::fwTools::fwID::exist(HasSlotId))
        {
            ::fwTools::Object::sptr obj      = ::fwTools::fwID::getObject(HasSlotId);
            ::fwCom::HasSlots::sptr hasSlots = std::dynamic_pointer_cast< ::fwCom::HasSlots >(obj);
            SLM_ASSERT("Object with id " << HasSlotId << " is not a HasSlots", hasSlots);

            ::fwCom::SlotBase::sptr slot = hasSlots->slot(slotKey);

            slot->asyncRun();
        }
    }
}

//-----------------------------------------------------------------------------

void SSlotCaller::configuring() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();
    this->initialize();

    ConfigurationType cfg = m_configuration->findConfigurationElement("slots");

    ::fwRuntime::ConfigurationElementContainer slotCfgs = cfg->findAllConfigurationElement("slot");

    ::boost::regex re("(.*)/(.*)");
    ::boost::smatch match;
    std::string src, uid, key;

    for(ConfigurationType elem :   slotCfgs.getElements())
    {
        src = elem->getValue();
        if( ::boost::regex_match(src, match, re) )
        {
            OSLM_ASSERT("Wrong value for attribute src: "<<src, match.size() >= 3);
            uid.assign(match[1].first, match[1].second);
            key.assign(match[2].first, match[2].second);

            SLM_ASSERT("Missing hasSlotsId attribute", !uid.empty());
            SLM_ASSERT("Missing slotKey attribute", !key.empty());

            m_slotInfos.push_back( std::make_pair(uid, key) );
        }
    }
}

//-----------------------------------------------------------------------------

} // namespace action
} // namespace gui

