/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __UIMEASUREMENT_ACTION_REMOVELANDMARK_HPP__
#define __UIMEASUREMENT_ACTION_REMOVELANDMARK_HPP__

#include <fwData/Image.hpp>
#include <fwData/Point.hpp>

#include <fwGui/IActionSrv.hpp>

#include "uiMeasurement/config.hpp"


namespace uiMeasurement
{

namespace action
{

/**
 * @brief   This action removes landmarks.
 * @class   RemoveLandmark
 *
 * @date    2010.
 */
class UIMEASUREMENT_CLASS_API RemoveLandmark : public ::fwGui::IActionSrv
{
public:
    fwCoreServiceClassDefinitionsMacro ( (RemoveLandmark)( ::fwGui::IActionSrv) );

    UIMEASUREMENT_API RemoveLandmark() throw();

    UIMEASUREMENT_API virtual ~RemoveLandmark() throw();

protected:


    void configuring() throw (::fwTools::Failed);

    void starting() throw (::fwTools::Failed);

    void updating() throw (::fwTools::Failed);

    void stopping() throw (::fwTools::Failed);

    void info(std::ostream &_sstream );

private:
    void notify( ::fwData::Image::sptr image, ::fwData::Point::sptr backup );

    ::fwData::Point::sptr  getLandmarkToRemove(::fwData::Image::sptr image, bool &removeAll);
};

} // namespace action

} // namespace uiMeasurement

#endif // __UIMEASUREMENT_ACTION_REMOVELANDMARK_HPP__
