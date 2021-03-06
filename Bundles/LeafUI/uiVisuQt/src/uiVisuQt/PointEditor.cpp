/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "uiVisuQt/PointEditor.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slot.hxx>
#include <fwCom/Slots.hpp>
#include <fwCom/Slots.hxx>

#include <fwCore/base.hpp>

#include <fwData/Composite.hpp>
#include <fwData/String.hpp>

#include <fwGuiQt/container/QtContainer.hpp>

#include <fwMath/IntrasecTypes.hpp>

#include <fwServices/macros.hpp>
#include <fwServices/IService.hpp>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>
#include <QDoubleValidator>
#include <QLabel>
#include <QPalette>
#include <QSpacerItem>

namespace uiVisu
{

fwServicesRegisterMacro( ::gui::editor::IEditor, ::uiVisu::PointEditor, ::fwData::Composite );

static const ::fwCom::Slots::SlotKeyType s_GET_INTERACTION_SLOT = "getInteraction";

PointEditor::PointEditor() throw()
{
    newSlot(s_GET_INTERACTION_SLOT, &PointEditor::getInteraction, this);
}

//------------------------------------------------------------------------------

PointEditor::~PointEditor() throw()
{
}

//------------------------------------------------------------------------------

void PointEditor::starting() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->::fwGui::IGuiContainerSrv::create();

    ::fwGuiQt::container::QtContainer::sptr qtContainer = ::fwGuiQt::container::QtContainer::dynamicCast(
        this->getContainer() );
    QWidget* const container = qtContainer->getQtContainer();
    SLM_ASSERT("container not instanced", container);

    QHBoxLayout* hLayout = new QHBoxLayout();

    QLabel* staticText_x = new QLabel( tr("x:"), container);
    hLayout->addWidget( staticText_x, 0, Qt::AlignVCenter );

    m_textCtrl_x = new QLineEdit( container );
    m_textCtrl_x->setValidator( new QDoubleValidator(m_textCtrl_x) );
    hLayout->addWidget( m_textCtrl_x, 1, Qt::AlignVCenter );

    QLabel* staticText_y = new QLabel( tr("y:"), container );
    hLayout->addWidget( staticText_y, 0, Qt::AlignVCenter );

    m_textCtrl_y = new QLineEdit( container );
    m_textCtrl_y->setValidator( new QDoubleValidator(m_textCtrl_y) );
    hLayout->addWidget( m_textCtrl_y, 1, Qt::AlignVCenter );

    QLabel* staticText_z = new QLabel( tr("z:"), container );
    hLayout->addWidget( staticText_z, 0, Qt::AlignVCenter );

    m_textCtrl_z = new QLineEdit( container );
    m_textCtrl_z->setValidator( new QDoubleValidator(m_textCtrl_z) );
    hLayout->addWidget( m_textCtrl_z, 1, Qt::AlignVCenter );


    container->setLayout( hLayout );
    this->updating();
}

//------------------------------------------------------------------------------

void PointEditor::stopping() throw(::fwTools::Failed)
{
    SLM_TRACE_FUNC();

    this->getContainer()->clean();
    this->::fwGui::IGuiContainerSrv::destroy();
}

//------------------------------------------------------------------------------

void PointEditor::configuring() throw(fwTools::Failed)
{
    SLM_TRACE_FUNC();
    this->::fwGui::IGuiContainerSrv::initialize();
}

//------------------------------------------------------------------------------

void PointEditor::updating() throw(::fwTools::Failed)
{
}

//------------------------------------------------------------------------------

void PointEditor::swapping() throw(::fwTools::Failed)
{
    this->updating();
}

//------------------------------------------------------------------------------

void PointEditor::getInteraction(::fwComEd::PickingInfo info)
{
    if ( info.m_eventId == ::fwComEd::PickingInfo::Event::MOUSE_MOVE )
    {
        m_textCtrl_x->setText(QString("%1").arg(info.m_worldPos[0], 0, 'f', 0));
        m_textCtrl_y->setText(QString("%1").arg(info.m_worldPos[1], 0, 'f', 0));
        m_textCtrl_z->setText(QString("%1").arg(info.m_worldPos[2], 0, 'f', 0));
    }
}

//------------------------------------------------------------------------------

void PointEditor::info( std::ostream &_sstream )
{
    _sstream << "Point Editor";
}

//------------------------------------------------------------------------------
}

