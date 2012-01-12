/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2010.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef _FWXML_XML_RECONSTRUCTIONXMLTRANSLATOR_HPP_
#define _FWXML_XML_RECONSTRUCTIONXMLTRANSLATOR_HPP_

#include <fwData/Reconstruction.hpp>

#include "fwXML/XML/XMLTranslator.hpp"

namespace fwXML
{

class FWXML_CLASS_API ReconstructionXMLTranslator : public XMLTranslator
{
public:

    /// trivial constructor
    FWXML_API ReconstructionXMLTranslator() ;

    /// trivial destructor
    FWXML_API virtual ~ReconstructionXMLTranslator() ;

    /// get XML from current object
    FWXML_API xmlNodePtr getXMLFrom( ::fwTools::Object::sptr obj );


    /// get Object from an XML node
    FWXML_API void updateDataFromXML( ::fwTools::Object::sptr toUpdate,  xmlNodePtr source);
};

}

#endif /*_FWXML_XML_RECONSTRUCTIONXMLTRANSLATOR_HPP_*/