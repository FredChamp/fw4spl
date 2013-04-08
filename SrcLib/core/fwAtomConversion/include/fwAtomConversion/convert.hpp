/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2013.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWATOMCONVERSION_CONVERT_HPP__
#define __FWATOMCONVERSION_CONVERT_HPP__

#include <fwData/Object.hpp>
#include <fwAtoms/Object.hpp>

#include "fwAtomConversion/config.hpp"
#include "fwAtomConversion/DataVisitor.hpp"
#include "fwAtomConversion/AtomVisitor.hpp"

namespace fwAtomConversion
{

    /**
     * @brief Helper to convert a ::fwData::Object to a ::fwAtoms::Object
     *
     * @param data data object to convert
     * @return Converted ::fwAtoms::Object
     *
     * @throw ::camp::ClassNotFound if data class is not found.
     */
    FWATOMCONVERSION_API ::fwAtoms::Object::sptr convert( ::fwData::Object::sptr data );

    /**
     * @brief Converts a ::fwData::Object to a ::fwAtoms::Object.
     * @param dataObj data to convert
     * @param cache   cache to register already converted data, used when a data is referenced multiple times.
     * @return Returns the converted atom.
     * @throw ::camp::ClassNotFound if data class is not found.
     */
    FWATOMCONVERSION_API ::fwAtoms::Object::sptr convert( ::fwData::Object::sptr dataObj,
                                                          DataVisitor::AtomCacheType & cache );

    /**
     * @brief Helper to convert a ::fwAtoms::Object to a ::fwData::Object
     *
     * @param atom atom to convert
     * @return Converted ::fwData::Object
     *
     * @throw ::fwAtomConversion::exception::DataFactoryNotFound if the data class is not found.
     * @throw ::fwAtomConversion::exception::DuplicatedDataUUID if the data uuid already exists in the system.
     */
    FWATOMCONVERSION_API ::fwData::Object::sptr convert( ::fwAtoms::Object::sptr atom );

    /**
     * @brief Converts a ::fwAtoms::Object to a ::fwData::Object
     *
     * @param atom atom to convert
     * @param cache  cache to register the atoms already converted, used when an atom is referenced multiple times
     * @return Converted ::fwData::Object.
     *
     * @throw ::fwAtomConversion::exception::DataFactoryNotFound if the data class is not found.
     * @throw ::fwAtomConversion::exception::DuplicatedDataUUID if the data uuid already exists in the system.
     */
    FWATOMCONVERSION_API ::fwData::Object::sptr convert( ::fwAtoms::Object::sptr atomObj,
                                                         AtomVisitor::DataCacheType & cache );

} // end namespace fwAtomConversion

#endif // __FWATOMCONVERSION_CONVERT_HPP__