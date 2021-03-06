/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiIO/action/SSeriesDBMerger.hpp"

#include <fwCom/Signal.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwComEd/helper/SeriesDB.hpp>

#include <fwGui/Cursor.hpp>

#include <fwJobs/IJob.hpp>

#include <fwMedData/Series.hpp>

#include <fwServices/macros.hpp>
#include <fwServices/op/Add.hpp>
#include <fwServices/registry/ServiceConfig.hpp>

namespace uiIO
{
namespace action
{

fwServicesRegisterMacro( ::fwGui::IActionSrv, ::uiIO::action::SSeriesDBMerger, ::fwMedData::SeriesDB );

static const ::fwCom::Signals::SignalKeyType JOB_CREATED_SIGNAL = "jobCreated";
static const ::fwCom::Slots::SlotKeyType FORWARD_JOB_SLOT       = "forwardJob";

//------------------------------------------------------------------------------

SSeriesDBMerger::SSeriesDBMerger( ) throw() :
    m_ioSelectorSrvConfig ("IOSelectorServiceConfigVRRenderReader")
{
    m_sigJobCreated  = newSignal< JobCreatedSignalType >( JOB_CREATED_SIGNAL );
    m_slotForwardJob = newSlot( FORWARD_JOB_SLOT, &SSeriesDBMerger::forwardJob, this );
}

//------------------------------------------------------------------------------

SSeriesDBMerger::~SSeriesDBMerger() throw()
{
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::info(std::ostream &_sstream )
{
    _sstream << "Action for add SeriesDB" << std::endl;
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::configuring() throw( ::fwTools::Failed )
{
    SLM_TRACE_FUNC();

    this->::fwGui::IActionSrv::initialize();
    std::vector < ConfigurationType > vectConfig = m_configuration->find("IOSelectorSrvConfig");
    if(!vectConfig.empty())
    {
        ConfigurationType selectorConfig = vectConfig.at(0);
        SLM_ASSERT("Missing 'name' attribute", selectorConfig->hasAttribute("name"));
        m_ioSelectorSrvConfig = selectorConfig->getAttributeValue("name");
    }
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::updating( ) throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    ::fwGui::LockAction lock(this->getSptr());
    ::fwMedData::SeriesDB::sptr seriesDB = this->getObject< ::fwMedData::SeriesDB >();
    SLM_ASSERT("SeriesDB not instanced", seriesDB);

    // Create a new SeriesDB
    ::fwMedData::SeriesDB::sptr localSeriesDB = ::fwMedData::SeriesDB::New();

    /// Create IOSelectorService on the new SeriesDB and execute it.

    // Get the config
    ::fwRuntime::ConfigurationElement::csptr ioCfg;
    ioCfg = ::fwServices::registry::ServiceConfig::getDefault()->getServiceConfig(m_ioSelectorSrvConfig,
                                                                                  "::uiIO::editor::SIOSelector");
    SLM_ASSERT("There is no service configuration "
               << m_ioSelectorSrvConfig
               << " for ::uiIO::editor::SIOSelector", ioCfg);

    // Init and execute the service
    ::fwServices::IService::sptr ioSelectorSrv;
    ioSelectorSrv = ::fwServices::add(localSeriesDB,
                                      "::gui::editor::IDialogEditor",
                                      "::uiIO::editor::SIOSelector");

    ioSelectorSrv->setWorker(m_associatedWorker);

    auto jobCreatedSignal = ioSelectorSrv->signal("jobCreated");
    if(jobCreatedSignal)
    {
        jobCreatedSignal->connect(m_slotForwardJob);
    }

    ioSelectorSrv->setConfiguration( ::fwRuntime::ConfigurationElement::constCast(ioCfg) );
    ioSelectorSrv->configure();
    ioSelectorSrv->start();
    ioSelectorSrv->update();
    ioSelectorSrv->stop();
    ::fwServices::OSR::unregisterService( ioSelectorSrv );

    ::fwComEd::helper::SeriesDB sDBhelper(seriesDB);
    sDBhelper.merge(localSeriesDB);
    sDBhelper.notify();
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::starting() throw (::fwTools::Failed)
{
    this->::fwGui::IActionSrv::actionServiceStarting();
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::stopping() throw (::fwTools::Failed)
{
    this->::fwGui::IActionSrv::actionServiceStopping();
}

//------------------------------------------------------------------------------

void SSeriesDBMerger::forwardJob(::fwJobs::IJob::sptr iJob)
{
    m_sigJobCreated->emit(iJob);
}

//------------------------------------------------------------------------------
//
} // namespace action
} // namespace uiIO
