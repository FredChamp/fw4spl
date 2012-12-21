/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2012.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _OPSOFA_SOFACORESRV_HPP_
#define _OPSOFA_SOFACORESRV_HPP_

#include "config.hpp"
#include <fwGui/IActionSrv.hpp>
#include "opSofa/SofaBusiness.hpp"

namespace opSofa
{


/**
 * @brief Service allow to manage opSofa bundle
 */
class SofaCoreSrv : public ::fwGui::IActionSrv
{

public :
    fwCoreServiceClassDefinitionsMacro ( (SofaCoreSrv)(::fwGui::IActionSrv) );

    SofaCoreSrv() throw() ;
    virtual ~SofaCoreSrv() throw() ;

protected:
    void configuring() throw ( ::fwTools::Failed );
    void starting() throw ( ::fwTools::Failed );
    void stopping() throw ( ::fwTools::Failed );
    void updating() throw ( ::fwTools::Failed );
    void receiving( fwServices::ObjectMsg::csptr _pMsg ) throw ( ::fwTools::Failed );
    void info ( std::ostream &_sstream ) ;
    void addMesh(std::string, std::string);

private :

    /**
     * @brief SofaBusiness pointer
     */
    SofaBusiness *sofa;
};

} // namespace opSofa


#endif // _OPSOFA_SOFACORESRV_HPP_
