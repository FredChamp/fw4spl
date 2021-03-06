/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIMEDDATAQT_EDITOR_SSELECTOR_HPP__
#define __UIMEDDATAQT_EDITOR_SSELECTOR_HPP__


#include "uiMedDataQt/config.hpp"
#include "uiMedDataQt/widget/Selector.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwData/Vector.hpp>

#include <fwMedData/SeriesDB.hpp>

#include <gui/editor/IEditor.hpp>

#include <QAbstractItemView>
#include <QPointer>
#include <QObject>
#include <QVector>


namespace uiMedData
{
namespace editor
{
/**
 * @brief   This editor shows information about the medical data. It allows to manipulate
 *          (select, erase, ...) studies and series.
 *
 * @section XML XML Configuration
 *
 * @code{.xml}
    <service uid="..." type="::uiMedData::editor::SSelector">
        <inout key="seriesDB" uid="..." />
        <inout key="selection" uid="..." />
        <selectionMode>single|extended</selectionMode>
        <allowedRemove>yes|no</allowedRemove>
        <insertMode>yes|no</insertMode>
        <icons>
            <icon series="..." icon="..." />
            <icon series="..." icon="..." />
        </icons>
    </service>
   @endcode
 * @subsection In-Out In-Out
 * - \b seriesDB [::fwMedData::SeriesDB]: seriesDB on which the editor operates.
 * - \b selection [::fwData::Vector]: defines the id of the ::fwData::Vector where the selection will be put or get.
 * @subsection Configuration Configuration
 * - \b selectionMode : defines the selection mode for the series, among {"single", "extended"}, where extended means "multiple"
 * - \b allowedRemove : allows user to remove series, among {"yes", "no"}
 * - \b insertMode : only allows selection of uiMedData::InsertSeries, among {"yes", "no"}
 * - \b icons : defines the icon to associate for a series
 *    - \b series : the series classname, e.g. {::fwMedData::ImageSeries, ::fwMedData::ModelSeries, ...}
 *    - \b icon : the icon path
 */
class UIMEDDATAQT_CLASS_API SSelector : public QObject,
                                        public ::gui::editor::IEditor
{
Q_OBJECT
public:
    fwCoreServiceClassDefinitionsMacro ( (SSelector)(::gui::editor::IEditor) );

    /// Constructor
    UIMEDDATAQT_API SSelector();

    /// Destructor
    UIMEDDATAQT_API virtual ~SSelector() throw();

    typedef ::fwCom::Signal< void ( SPTR( ::fwMedData::Series ) ) > SeriesDoubleClickedSignalType;

    /// Key in m_signals map of signal m_sigSeriesDoubleClicked
    UIMEDDATAQT_API static const ::fwCom::Signals::SignalKeyType s_SERIES_DOUBLE_CLICKED_SIG;

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     *
     * Connect SeriesDB::s_ADDED_SERIES_SIG to this::s_ADD_SERIES_SLOT
     * Connect SeriesDB::s_REMOVED_SERIES_SIG to this::s_REMOVE_SERIES_SLOT
     */
    UIMEDDATAQT_API virtual KeyConnectionsType getObjSrvConnections() const;

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     *
     * Connect SeriesDB::s_ADDED_SERIES_SIG to this::s_ADD_SERIES_SLOT
     * Connect SeriesDB::s_REMOVED_SERIES_SIG to this::s_REMOVE_SERIES_SLOT
     */
    UIMEDDATAQT_API virtual KeyConnectionsMap getAutoConnections() const;

protected:

    /// Installs GUI : create container and add selector.
    virtual void starting() throw(::fwTools::Failed);

    /// Destroys GUI.
    virtual void stopping() throw(::fwTools::Failed);

    /// Configures the service according to the xml tags found.
    virtual void configuring() throw (::fwTools::Failed);

    /// Fill selector with the series contained in SeriesDB.
    virtual void updating() throw (::fwTools::Failed);

    virtual void info( std::ostream& _sstream );

protected Q_SLOTS:

    /**
     * @brief Manages the selection vector according to selection/deselection.
     * @param[in] selection series to add in selection vector.
     * @param[in] deselection series to remove from selection vector.
     */
    void onSelectedSeries(QVector< ::fwMedData::Series::sptr > selection,
                          QVector< ::fwMedData::Series::sptr > deselection);

    /**
     * @brief Send a 'seriesDoubleClicked' signal when the user double click on a series. This signal holds the
     * clicked series.
     * @param[in] index index of the clicked item in the selector.
     * @todo  Manages double click on a study.
     */
    void onDoubleClick(const QModelIndex& index);

    /**
     * @brief Removes series from seriesDB and notify.
     * @param[in] selection series to remove from seriesDB.
     */
    void onRemoveSeries(QVector< ::fwMedData::Series::sptr > selection);

private:

    /**
     * @name Slots
     * @{
     */
    static const ::fwCom::Slots::SlotKeyType s_ADD_SERIES_SLOT;
    static const ::fwCom::Slots::SlotKeyType s_REMOVE_SERIES_SLOT;
    typedef ::fwCom::Slot<void (::fwMedData::SeriesDB::ContainerType)> RemoveSeriesSlotType;

    /// Slot: add series into the selector
    void addSeries(::fwMedData::SeriesDB::ContainerType addedSeries);
    /// Slot: remove series from the selector
    void removeSeries(::fwMedData::SeriesDB::ContainerType removedSeries);

    /// Slot used to remove series from the selector
    RemoveSeriesSlotType::sptr m_slotRemoveSeries;
    /**
     * @}
     */

    /// Returns current selection vector given by its fwID m_selectionId.
    ::fwData::Vector::sptr getSelection();

    /// fwID of the vector of selections
    std::string m_selectionId;

    /// Selector widget.
    QPointer< ::uiMedData::widget::Selector > m_selectorWidget;

    /// Signal emitted when there is a double click on a series
    SeriesDoubleClickedSignalType::sptr m_sigSeriesDoubleClicked;

    /// Map containing the specified icons for a series (map\<series classname, icon path\>)
    ::uiMedData::widget::Selector::SeriesIconType m_seriesIcons;

    /// Permits the user to remove series. Default is yes
    bool m_allowedRemove;

    /// Change the behaviour of the treeview selection mode
    QAbstractItemView::SelectionMode m_selectionMode;

    /// If true, allows selection of uiMedData::InsertSeries only
    bool m_insertMode;

};
} // namespace editor
} // namespace uiMedData

#endif // __UIMEDDATAQT_EDITOR_SSELECTOR_HPP__

