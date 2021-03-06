/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "fwComEd/helper/SeriesDB.hpp"

#include <fwCom/Signal.hpp>
#include <fwCom/Signal.hxx>
#include <fwCom/Signals.hpp>

#include <fwMedData/SeriesDB.hpp>
#include <fwServices/IService.hpp>

namespace fwComEd
{
namespace helper
{

//-----------------------------------------------------------------------------

SeriesDB::SeriesDB( ::fwMedData::SeriesDB::wptr seriesDB ) :
    m_seriesDB ( seriesDB )
{
}

//-----------------------------------------------------------------------------

SeriesDB::~SeriesDB()
{
}

//-----------------------------------------------------------------------------

void SeriesDB::add( ::fwMedData::Series::sptr newSeries )
{
    ::fwMedData::SeriesDB::sptr seriesDB = m_seriesDB.lock();
    OSLM_ASSERT( "The object " << newSeries->getID() << " must not exist in SeriesDB.",
                 std::find(seriesDB->begin(), seriesDB->end(), newSeries) == seriesDB->end());

    // Modify SeriesDB
    seriesDB->getContainer().push_back( newSeries );

    m_addedSeries.push_back(newSeries);

}

//-----------------------------------------------------------------------------

void SeriesDB::remove( ::fwMedData::Series::sptr oldSeries )
{
    ::fwMedData::SeriesDB::sptr seriesDB = m_seriesDB.lock();
    ::fwMedData::SeriesDB::iterator iter = std::find(seriesDB->begin(), seriesDB->end(), oldSeries);
    OSLM_ASSERT( "The object " << oldSeries->getID() << " must exist in SeriesDB.",
                 iter != seriesDB->end());

    // Modify SeriesDB
    seriesDB->getContainer().erase( iter );

    m_removedSeries.push_back( oldSeries );

}

//-----------------------------------------------------------------------------

void SeriesDB::clear()
{
    ::fwMedData::SeriesDB::sptr seriesDB = m_seriesDB.lock();

    while (!seriesDB->empty())
    {
        this->remove(seriesDB->front());
    }
}

//-----------------------------------------------------------------------------

void SeriesDB::merge(::fwMedData::SeriesDB::sptr seriesDBIn)
{
    ::fwMedData::SeriesDB::ContainerType& vectIn = seriesDBIn->getContainer();
    for(::fwMedData::Series::sptr series :  vectIn)
    {
        this->add(series);
    }
}

//-----------------------------------------------------------------------------

void SeriesDB::notify()
{
    if (!m_addedSeries.empty())
    {
        auto sig = m_seriesDB.lock()->signal< ::fwMedData::SeriesDB::AddedSeriesSignalType >(
            ::fwMedData::SeriesDB::s_ADDED_SERIES_SIG);
        sig->asyncEmit(m_addedSeries);

    }

    if (!m_removedSeries.empty())
    {
        auto sig = m_seriesDB.lock()->signal< ::fwMedData::SeriesDB::RemovedSeriesSignalType >(
            ::fwMedData::SeriesDB::s_REMOVED_SERIES_SIG);
        sig->asyncEmit(m_removedSeries);

    }

    OSLM_INFO_IF("No changes were found on the SeriesDB '" + m_seriesDB.lock()->getID() + "', nothing to notify.",
                 m_addedSeries.empty() && m_removedSeries.empty());
}

//-----------------------------------------------------------------------------

} // namespace helper
} // namespace fwComEd
