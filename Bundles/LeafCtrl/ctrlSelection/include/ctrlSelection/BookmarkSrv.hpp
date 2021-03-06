/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __CTRLSELECTION_BOOKMARKSRV_HPP__
#define __CTRLSELECTION_BOOKMARKSRV_HPP__

#include <fwServices/IService.hpp>
#include <fwServices/IController.hpp>

#include "ctrlSelection/config.hpp"

namespace ctrlSelection
{


/**
 * @class  BookmarkSrv
 * @brief  This service bookmark its object with the name given in configuration.
 */
class CTRLSELECTION_CLASS_API BookmarkSrv : public ::fwServices::IController
{

public:

    fwCoreServiceClassDefinitionsMacro ( (BookmarkSrv)(::fwServices::IController) );

    CTRLSELECTION_API BookmarkSrv() throw();

    CTRLSELECTION_API virtual ~BookmarkSrv() throw();

protected:

    /// Adds the object in bookmark.
    CTRLSELECTION_API virtual void starting()  throw ( ::fwTools::Failed );

    /// Removes the object from bookmark
    CTRLSELECTION_API virtual void stopping()  throw ( ::fwTools::Failed );

    /// Do nothing
    CTRLSELECTION_API virtual void swapping()  throw ( ::fwTools::Failed );

    /**
     * @code{.xml}
       <service impl="::ctrlSelection::BookmarkSrv" type="::fwServices::IController" autoConnect="no">
           <bookmark fromString="..." name="..." />
       </service>
       @endcode
     * - \b fromString : prefix of the bookmark key
     * - \b name : name of the bookmark
     * The prefix and the name are concatenated as 'prefix_name'.
     */
    CTRLSELECTION_API virtual void configuring()  throw ( ::fwTools::Failed );

    /// Do nothing
    CTRLSELECTION_API virtual void reconfiguring()  throw ( ::fwTools::Failed );

    /// Do nothing
    CTRLSELECTION_API virtual void updating() throw ( ::fwTools::Failed );

    CTRLSELECTION_API virtual void info( std::ostream &_sstream );

private:
    std::string m_bookmarkName;
};

} // ctrlSelection

#endif // __CTRLSELECTION_BOOKMARKSRV_HPP__
