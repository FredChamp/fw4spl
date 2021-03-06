/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiImageQt/ImageTransparency.hpp"

#include <fwCom/Signal.hpp>
#include <fwCom/Signal.hxx>
#include <fwCom/Signals.hpp>

#include <fwComEd/fieldHelper/MedicalImageHelpers.hpp>

#include <fwCore/base.hpp>

#include <fwData/Boolean.hpp>
#include <fwData/Image.hpp>

#include <fwGuiQt/container/QtContainer.hpp>

#include <fwMath/IntrasecTypes.hpp>

#include <fwServices/macros.hpp>
#include <fwServices/IService.hpp>

#include <QHBoxLayout>
#include <QLabel>
#include <QWidget>

namespace uiImage
{

fwServicesRegisterMacro( ::gui::editor::IEditor, ::uiImage::ImageTransparency, ::fwData::Image );


ImageTransparency::ImageTransparency() throw()
{
}

//------------------------------------------------------------------------------

ImageTransparency::~ImageTransparency() throw()
{
}

//------------------------------------------------------------------------------

void ImageTransparency::starting() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->::fwGui::IGuiContainerSrv::create();
    ::fwData::Image::sptr image = this->getObject< ::fwData::Image >();

    ::fwGuiQt::container::QtContainer::sptr qtContainer = ::fwGuiQt::container::QtContainer::dynamicCast(
        this->getContainer() );
    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    QHBoxLayout* hLayout = new QHBoxLayout();

    QLabel* staticText = new QLabel( QObject::tr("Transparency: "), container);
    hLayout->addWidget( staticText, 0, Qt::AlignVCenter );

    m_valueSlider = new QSlider( Qt::Horizontal, container );
    hLayout->addWidget( m_valueSlider, 1, Qt::AlignVCenter );
    m_valueSlider->setRange(0, 100);
    m_valueSlider->setMinimumWidth(100);

    m_valueCheckBox = new QCheckBox( QObject::tr("visible"), container);
    m_action        = new QAction(container);
    m_action->setCheckable(true);
    if (!m_shortcut.empty())
    {
        m_action->setShortcut(QKeySequence(QString::fromStdString(m_shortcut)));
    }
    m_valueCheckBox->addAction(m_action);
    hLayout->addWidget( m_valueCheckBox, 0, Qt::AlignVCenter );

    container->setLayout( hLayout );

    QObject::connect(m_valueSlider, SIGNAL(valueChanged(int)), this, SLOT(onModifyTransparency(int)));
    QObject::connect(m_valueCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onModifyVisibility(int)));
    QObject::connect(m_action, SIGNAL(triggered(bool)), this, SLOT(onModifyVisibility(bool)));

    this->updating();
}

//------------------------------------------------------------------------------

void ImageTransparency::stopping() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    QObject::disconnect(m_valueSlider, SIGNAL(valueChanged(int)), this, SLOT(onModifyTransparency(int)));
    QObject::disconnect(m_valueCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onModifyVisibility(int)));
    QObject::disconnect(m_action, SIGNAL(triggered(bool)), this, SLOT(onModifyVisibility(bool)));

    this->getContainer()->clean();
    this->::fwGui::IGuiContainerSrv::destroy();
}

//------------------------------------------------------------------------------

void ImageTransparency::configuring() throw(fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->::fwGui::IGuiContainerSrv::initialize();

    //<shortcut value="X"/>
    std::vector < ConfigurationType > vectCfg = m_configuration->find("shortcut");
    if(!vectCfg.empty())
    {
        ConfigurationType config = vectCfg.at(0);
        SLM_ASSERT("Missing attribute value", config->hasAttribute("value"));
        m_shortcut = config->getAttributeValue("value");
    }
}

//------------------------------------------------------------------------------

void ImageTransparency::updating() throw(::fwTools::Failed)
{
    ::fwData::Image::sptr img = this->getObject< ::fwData::Image >();

    bool imageIsValid = ::fwComEd::fieldHelper::MedicalImageHelpers::checkImageValidity( img );
    m_valueSlider->setEnabled(imageIsValid);
    m_valueCheckBox->setEnabled(imageIsValid);
    if (imageIsValid)
    {
        QObject::disconnect(m_valueSlider, SIGNAL(valueChanged(int)), this, SLOT(onModifyTransparency(int)));
        QObject::disconnect(m_valueCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onModifyVisibility(int)));
        QObject::disconnect(m_action, SIGNAL(triggered(bool)), this, SLOT(onModifyVisibility(bool)));

        if(img->getField( "TRANSPARENCY" ) )
        {
            ::fwData::Integer::sptr transparency = img->getField< ::fwData::Integer >( "TRANSPARENCY" );
            m_valueSlider->setValue( *transparency );
        }
        else
        {
            img->setField( "TRANSPARENCY", ::fwData::Integer::New(0) );
            m_valueSlider->setValue( 0 );
        }
        if(img->getField( "VISIBILITY" ) )
        {
            ::fwData::Boolean::sptr visible = img->getField< ::fwData::Boolean >( "VISIBILITY" );
            m_valueCheckBox->setChecked( *visible );
            m_action->setChecked(*visible);
        }
        else
        {
            img->setField( "VISIBILITY", ::fwData::Boolean::New(true) );
            m_valueCheckBox->setChecked( true );
            m_action->setChecked(true);
        }
        QObject::connect(m_valueSlider, SIGNAL(valueChanged(int)), this, SLOT(onModifyTransparency(int)));
        QObject::connect(m_valueCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onModifyVisibility(int)));
        QObject::connect(m_action, SIGNAL(triggered(bool)), this, SLOT(onModifyVisibility(bool)));
    }
}

//------------------------------------------------------------------------------

void ImageTransparency::swapping() throw(::fwTools::Failed)
{
    this->updating();
}

//------------------------------------------------------------------------------

void ImageTransparency::info( std::ostream &_sstream )
{
    _sstream << "Image Features Editor";
}

//------------------------------------------------------------------------------

void ImageTransparency::onModifyTransparency(int value)
{
    SLM_TRACE_FUNC();
    ::fwData::Image::sptr img = this->getObject< ::fwData::Image >();
    img->setField( "TRANSPARENCY",  ::fwData::Integer::New(value) );

    auto sig = img->signal< ::fwData::Image::TransparencyModifiedSignalType >(
        ::fwData::Image::s_TRANSPARENCY_MODIFIED_SIG);
    {
        ::fwCom::Connection::Blocker block(sig->getConnection(m_slotUpdate));
        sig->asyncEmit();
    }
}

//------------------------------------------------------------------------------

void ImageTransparency::onModifyVisibility(bool value)
{
    SLM_TRACE_FUNC();
    m_valueCheckBox->setCheckState(value ? Qt::Checked : Qt::Unchecked);
    this->notifyVisibility(value);
}

//------------------------------------------------------------------------------

void ImageTransparency::onModifyVisibility(int value)
{
    SLM_TRACE_FUNC();
    m_action->setChecked(value == Qt::Checked);

    this->notifyVisibility(value == Qt::Checked);
}

//------------------------------------------------------------------------------

void ImageTransparency::notifyVisibility(bool isVisible)
{
    ::fwData::Image::sptr img = this->getObject< ::fwData::Image >();
    img->setField( "VISIBILITY",  ::fwData::Boolean::New(isVisible) );

    auto sig = img->signal< ::fwData::Image::VisibilityModifiedSignalType >(::fwData::Image::s_VISIBILITY_MODIFIED_SIG);
    {
        ::fwCom::Connection::Blocker block(sig->getConnection(m_slotUpdate));
        sig->asyncEmit(isVisible);
    }
}


//------------------------------------------------------------------------------

::fwServices::IService::KeyConnectionsType ImageTransparency::getObjSrvConnections() const
{
    KeyConnectionsType connections;
    connections.push_back( std::make_pair( ::fwData::Image::s_MODIFIED_SIG, s_UPDATE_SLOT ) );
    connections.push_back( std::make_pair( ::fwData::Image::s_VISIBILITY_MODIFIED_SIG, s_UPDATE_SLOT ) );
    connections.push_back( std::make_pair( ::fwData::Image::s_TRANSPARENCY_MODIFIED_SIG, s_UPDATE_SLOT ) );
    connections.push_back( std::make_pair( ::fwData::Image::s_BUFFER_MODIFIED_SIG, s_UPDATE_SLOT ) );

    return connections;
}

//------------------------------------------------------------------------------

}

