/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __IOVTK_PLUGIN_HPP__
#define __IOVTK_PLUGIN_HPP__

#include <fwRuntime/Plugin.hpp>

namespace ioVTK
{

class Plugin : public ::fwRuntime::Plugin
{
public:
    //! @brief Destructor.
    ~Plugin() throw();

    /**
     * @brief Start method.
     *
     * This method is used by runtime in order to initialize the bundle.
     *
     * @exception ::fwRuntime::RuntimeException
     */
    void start() throw(::fwRuntime::RuntimeException);

    /**
     * @brief Stop method.
     *
     * This method is used by runtime in order to close the bundle.
     */
    void stop() throw();

};

} // namespace ioVTK

#endif //__IOVTK_PLUGIN_HPP__
