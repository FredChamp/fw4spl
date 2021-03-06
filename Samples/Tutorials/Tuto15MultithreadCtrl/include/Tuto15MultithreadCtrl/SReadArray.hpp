/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __TUTO15MULTITHREADCTRL_SREADARRAY_HPP__
#define __TUTO15MULTITHREADCTRL_SREADARRAY_HPP__

#include "Tuto15MultithreadCtrl/config.hpp"

#include <fwServices/IController.hpp>


namespace Tuto15MultithreadCtrl
{

/**
 * @brief This service initializes a ::fwData::Array with 10 values (0 to 9).
 */
class TUTO15MULTITHREADCTRL_CLASS_API SReadArray : public ::fwServices::IController
{
public:

    fwCoreServiceClassDefinitionsMacro ( (SReadArray)(::fwServices::IController) );

    TUTO15MULTITHREADCTRL_API SReadArray() throw();
    TUTO15MULTITHREADCTRL_API virtual ~SReadArray() throw();

protected:

    /// Do nothing
    virtual void starting() throw(::fwTools::Failed);

    /// Do nothing
    virtual void stopping() throw(::fwTools::Failed);

    /// Initialize the current ::fwData::Array with 10 values (0 to 9).
    virtual void updating() throw(::fwTools::Failed);

    /// Do nothing
    virtual void configuring() throw(fwTools::Failed);
};

}  // namespace Tuto15MultithreadCtrl

#endif  // __TUTO15MULTITHREADCTRL_SREADARRAY_HPP__

