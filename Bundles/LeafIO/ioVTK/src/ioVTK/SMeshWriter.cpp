/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "ioVTK/SMeshWriter.hpp"

#include <fwCom/HasSignals.hpp>
#include <fwCom/Signal.hpp>
#include <fwCom/Signal.hxx>

#include <fwCore/base.hpp>

#include <fwData/location/Folder.hpp>
#include <fwData/location/SingleFile.hpp>
#include <fwData/Mesh.hpp>

#include <fwGui/Cursor.hpp>
#include <fwGui/dialog/LocationDialog.hpp>
#include <fwGui/dialog/MessageDialog.hpp>
#include <fwGui/dialog/ProgressDialog.hpp>

#include <fwJobs/IJob.hpp>

#include <fwServices/macros.hpp>

#include <fwVtkIO/MeshWriter.hpp>


namespace ioVTK
{

fwServicesRegisterMacro( ::io::IWriter, ::ioVTK::SMeshWriter, ::fwData::Mesh );

static const ::fwCom::Signals::SignalKeyType JOB_CREATED_SIGNAL = "jobCreated";

//------------------------------------------------------------------------------

SMeshWriter::SMeshWriter() throw()
{
    m_sigJobCreated = newSignal< JobCreatedSignalType >( JOB_CREATED_SIGNAL );
}

//------------------------------------------------------------------------------

::io::IOPathType SMeshWriter::getIOPathType() const
{
    return ::io::FILE;
}

//------------------------------------------------------------------------------

void SMeshWriter::configureWithIHM()
{
    SLM_TRACE_FUNC();
    static ::boost::filesystem::path _sDefaultPath("");

    ::fwGui::dialog::LocationDialog dialogFile;
    dialogFile.setTitle("Choose a vtk file to save Mesh");
    dialogFile.setDefaultLocation( ::fwData::location::Folder::New(_sDefaultPath) );
    dialogFile.addFilter("Vtk","*.vtk");
    dialogFile.setOption(::fwGui::dialog::ILocationDialog::WRITE);

    ::fwData::location::SingleFile::sptr result;
    result = ::fwData::location::SingleFile::dynamicCast( dialogFile.show() );
    if (result)
    {
        _sDefaultPath = result->getPath().parent_path();
        dialogFile.saveDefaultLocation( ::fwData::location::Folder::New(_sDefaultPath) );
        this->setFile(result->getPath());

    }
    else
    {
        this->clearLocations();
    }
}

//------------------------------------------------------------------------------

void SMeshWriter::starting() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
}

//------------------------------------------------------------------------------

void SMeshWriter::stopping() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
}

//------------------------------------------------------------------------------

void SMeshWriter::info(std::ostream &_sstream )
{
    _sstream << "SMeshWriter::info";
}

//------------------------------------------------------------------------------

void SMeshWriter::updating() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();

    if(  this->hasLocationDefined() )
    {
        // Retrieve dataStruct associated with this service
        ::fwData::Mesh::sptr pMesh = this->getObject< ::fwData::Mesh >();
        SLM_ASSERT("pMesh not instanced", pMesh);

        ::fwGui::Cursor cursor;
        cursor.setCursor(::fwGui::ICursor::BUSY);

        ::fwVtkIO::MeshWriter::sptr writer = ::fwVtkIO::MeshWriter::New();

        m_sigJobCreated->emit(writer->getJob());

        writer->setObject(pMesh);
        writer->setFile(this->getFile());

        try
        {
            writer->write();
        }
        catch (const std::exception & e)
        {
            std::stringstream ss;
            ss << "Warning during saving : " << e.what();

            ::fwGui::dialog::MessageDialog::showMessageDialog(
                "Warning",
                ss.str(),
                ::fwGui::dialog::IMessageDialog::WARNING);
        }
        catch( ... )
        {
            ::fwGui::dialog::MessageDialog::showMessageDialog(
                "Warning",
                "Warning during saving",
                ::fwGui::dialog::IMessageDialog::WARNING);
        }

        cursor.setDefaultCursor();
    }
}

//------------------------------------------------------------------------------

} // namespace ioVtk
