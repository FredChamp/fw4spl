/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWTHREAD_TIMER_HPP__
#define __FWTHREAD_TIMER_HPP__

#include <boost/chrono/duration.hpp>

#include <fwCore/mt/types.hpp>

#include "fwThread/Worker.hpp"
#include "fwThread/config.hpp"

#include <functional>

namespace fwThread
{

/**
 * @class Timer
 * @brief The Timer class provides single-shot or repetitive timers.
 * A Timer triggers a function once after a delay, or periodically, inside the
 * worker loop. The delay or the period is defined by the duration attribute.
 *
 * Timer's function must be set before starting the timer.
 *
 *
 * @date   2012.
 */
class FWTHREAD_CLASS_API Timer : public ::fwCore::BaseObject
{
public:
    /**
     * @name Typedefs
     * @{ */
    typedef std::shared_ptr< Timer >        sptr;
    typedef std::function< void () >         FunctionType;
    typedef ::boost::chrono::duration<double>   TimeDurationType;
    /**  @} */



    FWTHREAD_API ~Timer();

    /// Starts or restarts the timer.
    FWTHREAD_API virtual void start() = 0;

    /// Stops the timer and cancel all pending operations.
    FWTHREAD_API virtual void stop()
    {
    }

    /// Sets time duration.
    FWTHREAD_API virtual void setDuration(TimeDurationType duration) = 0;

    /// Sets the function to be triggered when time duration expires.
    template< typename F >
    void setFunction(F f)
    {
        ::fwCore::mt::ScopedLock lock(m_mutex);
        m_function = f;
        updatedFunction();
    }

    /// Returns if the timer mode is 'one shot'.
    virtual bool isOneShot() const = 0;

    /// Sets timer mode.
    virtual void setOneShot(bool oneShot) = 0;

    /// Returns true if the timer is currently running.
    virtual bool isRunning() const = 0;

protected:

    /**
     * @brief Constructs a Timer.
     * By default, a the Timer mode is repetitive.
     */
    FWTHREAD_API Timer();

    /// Copy constructor forbidden.
    Timer( const Timer& );

    /// Copy operator forbidden.
    Timer& operator=( const Timer& );

    /// This method is triggered when Timer's function is changed.
    FWTHREAD_API virtual void updatedFunction()
    {
    }

    /// Function object to execute each time the timer expires.
    FunctionType m_function;

    mutable ::fwCore::mt::Mutex m_mutex;
};

} //namespace fwThread

#endif //__FWTHREAD_TIMER_HPP__

