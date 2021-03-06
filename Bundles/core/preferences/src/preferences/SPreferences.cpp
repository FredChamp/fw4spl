/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2014-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "preferences/SPreferences.hpp"

#include <fwAtomsBoostIO/types.hpp>
#include <fwAtomsBoostIO/Reader.hpp>
#include <fwAtomsBoostIO/Writer.hpp>

#include <fwAtomConversion/convert.hpp>

#include <fwData/Composite.hpp>

#include <fwDataCamp/visitor/RecursiveLock.hpp>

#include <fwRuntime/ConfigurationElement.hpp>

#include <fwServices/macros.hpp>

#include <fwZip/ReadDirArchive.hpp>
#include <fwZip/WriteDirArchive.hpp>

#include <boost/filesystem.hpp>

namespace preferences
{

fwServicesRegisterMacro( ::preferences::IPreferencesService, ::preferences::SPreferences, ::fwData::Composite );

//-----------------------------------------------------------------------------

void SPreferences::starting() throw (::fwTools::Failed)
{
    this->load();
}

//-----------------------------------------------------------------------------

void SPreferences::stopping() throw (::fwTools::Failed)
{
    this->save();
}

//-----------------------------------------------------------------------------

void SPreferences::updating() throw (::fwTools::Failed)
{
    this->save();
}

//-----------------------------------------------------------------------------

void SPreferences::configuring() throw(::fwTools::Failed)
{
    std::vector < ::fwRuntime::ConfigurationElement::sptr > vectConfig = m_configuration->find("filename");
    SLM_ASSERT("The <filename> element must exist.", !vectConfig.empty() );
    m_prefFile = vectConfig.at(0)->getValue();
}

//-----------------------------------------------------------------------------

void SPreferences::load()
{
    if (::boost::filesystem::is_regular_file(m_prefFile))
    {
        const ::boost::filesystem::path folderPath = m_prefFile.parent_path();
        const ::boost::filesystem::path filename   = m_prefFile.filename();

        ::fwData::Object::sptr data = this->getObject< ::fwData::Object >();

        // Read atom
        ::fwZip::IReadArchive::sptr readArchive = ::fwZip::ReadDirArchive::New(folderPath.string());
        ::fwAtomsBoostIO::Reader reader;
        try
        {
            ::fwAtoms::Object::sptr atom = ::fwAtoms::Object::dynamicCast( reader.read( readArchive, filename ) );

            ::fwData::Object::sptr newData = ::fwAtomConversion::convert(atom,
                                                                         ::fwAtomConversion::AtomVisitor::ChangePolicy());
            data->shallowCopy(newData);
        }
        catch(...)
        {
            SLM_ERROR("Failed to load preference file '"+m_prefFile.string()+"'.");
        }
    }
}

//-----------------------------------------------------------------------------

void SPreferences::save()
{
    const ::boost::filesystem::path folderPath = m_prefFile.parent_path();
    const ::boost::filesystem::path filename   = m_prefFile.filename();

    ::fwData::Object::sptr obj = this->getObject();

    // Mutex data lock
    ::fwDataCamp::visitor::RecursiveLock recursiveLock (obj);

    // Convert data to atom
    ::fwAtoms::Object::sptr atom = ::fwAtomConversion::convert(obj);
    // Write atom
    ::fwZip::IWriteArchive::sptr writeArchive = ::fwZip::WriteDirArchive::New(folderPath.string());
    ::fwAtomsBoostIO::FormatType format       = ::fwAtomsBoostIO::JSON;

    if(::boost::filesystem::exists(m_prefFile) && ::boost::filesystem::is_regular_file(m_prefFile)
       && !(::boost::filesystem::status(m_prefFile).permissions() & ::boost::filesystem::owner_write) )
    {
        SLM_ERROR("SPreference need write access to the file '"+m_prefFile.string()+"'."
                  "Please, change file permission.");
    }
    else
    {
        ::fwAtomsBoostIO::Writer(atom).write( writeArchive, filename, format );
    }
}

//-----------------------------------------------------------------------------

}

