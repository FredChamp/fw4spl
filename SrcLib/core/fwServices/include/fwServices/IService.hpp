/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWSERVICES_ISERVICE_HPP__
#define __FWSERVICES_ISERVICE_HPP__

#include "fwServices/config.hpp"
#include "fwServices/factory/new.hpp"
#include "fwServices/helper/SigSlotConnection.hpp"

#include <fwCom/HasSignals.hpp>
#include <fwCom/HasSlots.hpp>
#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwData/Object.hpp>

#include <fwRuntime/ConfigurationElement.hpp>

#include <fwTools/Failed.hpp>
#include <fwTools/Object.hpp>

#include <boost/property_tree/ptree.hpp>

#include <cstdint>

namespace fwServices
{
namespace registry
{
class ObjectService;
}
namespace fwThread
{
class Worker;
}

#define KEY_GROUP_NAME(key, index) (key + "#" + std::to_string(index) )

/**
 * @brief   Base class for all services.
 *
 * This class defines the API to use and declare services.
 * The service state aims to impose the execution order (i.e. configure(), start(), update() or, stop()).
 *
 * @section Signals Signals
 * - \b started() : Emitted when the service has started.
 * - \b updated() : Emitted when the service has updated.
 * - \b stopped() : Emitted when the service has stopped.
 *
 * @section Slots Slots
 * - \b start() : Start the service.
 * - \b update() : Update the service.
 * - \b stop() : Stop the service.
 * - \b swap() : @deprecated Swap the current object.
 * - \b swapKey(const KeyType&, ::fwData::Object::sptr) : Swap the object at the given key with the object in parameter.
 */
class FWSERVICES_CLASS_API IService : public ::fwTools::Object,
                                      public ::fwCom::HasSlots,
                                      public ::fwCom::HasSignals
{

// to give to OSR an access on IService.m_associatedObject;
friend class registry::ObjectService;
friend class AppConfigManager2;

public:
    fwCoreServiceClassDefinitionsMacro ( (IService)(::fwTools::Object) );
    fwCoreAllowSharedFromThis();

    typedef ::boost::property_tree::ptree ConfigType;

    typedef std::string IdType;
    typedef std::string KeyType;
    typedef std::map< KeyType, CWPTR( ::fwData::Object )> InputMapType;
    typedef std::map< KeyType, WPTR( ::fwData::Object )> OutputMapType;

    enum class AccessType : std::uint8_t
    {
        INPUT,
        OUTPUT,
        INOUT,
    };

    /// Name of the key to identify the default Composite object that is used for services that don't work on any data.
    /// @remark For V1 compatibility purpose, this object is currently present on all services.
    FWSERVICES_API static const std::string s_DEFAULT_OBJECT;

    /**
     * @name Definition of service status
     */

    //@{

    /// Defines all possible global status for a service, including transitions
    typedef enum
    {
        STARTED,    /**< state after start */
        STARTING,   /**< state during start */
        SWAPPING,   /**< state during swap */
        STOPPED,    /**< state after stop */
        STOPPING    /**< state during stop */
    } GlobalStatus;

    /// Defines all possible status for an update process
    typedef enum
    {
        UPDATING,   /**< state during update */
        NOTUPDATING /**< state during when the service is not updating */
    } UpdatingStatus;

    /// Defines all possible status for a configuration process
    typedef enum
    {
        CONFIGURING,    /**< state during configuration */
        CONFIGURED,     /**< state after configuration */
        UNCONFIGURED    /**< state when the service is not configured */
    } ConfigurationStatus;

    //@}

    /**
     * @name Signal API
     */
    //@{
    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_STARTED_SIG;
    typedef ::fwCom::Signal<void ()> StartedSignalType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_UPDATED_SIG;
    typedef ::fwCom::Signal<void ()> UpdatedSignalType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_STOPPED_SIG;
    typedef ::fwCom::Signal<void ()> StoppedSignalType;

    //@}

    /**
     * @name Slot API
     */
    //@{
    typedef ::boost::shared_future< void > SharedFutureType;
    typedef ::boost::packaged_task< void > PackagedTaskType;
    typedef ::boost::future< void > UniqueFutureType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_START_SLOT;
    typedef ::fwCom::Slot<SharedFutureType()> StartSlotType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_STOP_SLOT;
    typedef ::fwCom::Slot<SharedFutureType()> StopSlotType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_UPDATE_SLOT;
    typedef ::fwCom::Slot<SharedFutureType()> UpdateSlotType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_SWAP_SLOT;
    typedef ::fwCom::Slot<SharedFutureType(::fwData::Object::sptr)> SwapSlotType;

    FWSERVICES_API static const ::fwCom::Slots::SlotKeyType s_SWAPKEY_SLOT;
    typedef ::fwCom::Slot<SharedFutureType(const KeyType&, ::fwData::Object::sptr)> SwapKeySlotType;

    /// Initializes m_associatedWorker and associates this worker to all service slots
    FWSERVICES_API void setWorker( SPTR(::fwThread::Worker) worker );

    /// Returns associate worker
    FWSERVICES_API SPTR(::fwThread::Worker) getWorker() const;

    //@}

    /**
     * @name Key service API
     */

    //@{

    /**
     * @brief Affect the configuration, using a generic XML like structure.
     * @param[in] _cfgElement a structure which represents the xml configuration
     * @post m_configurationState == UNCONFIGURED
     */
    FWSERVICES_API void setConfiguration( const ::fwRuntime::ConfigurationElement::sptr _cfgElement );

    /**
     * @brief Affect the configuration, using a boost property tree
     * @param[in] ptree property tree
     * @post m_configurationState == UNCONFIGURED
     */
    FWSERVICES_API void setConfiguration( const ConfigType& ptree );

    /**
     * @brief Invoke configuring() if m_globalState == STOPPED. Invoke reconfiguring() if m_globalState == STARTED. Does nothing otherwise.
     * @pre m_configurationState == UNCONFIGURED
     * @post m_configurationState == CONFIGURED
     * @note invoke checkConfiguration()
     */
    FWSERVICES_API void configure();

    /**
     * @brief Invoke starting() if m_globalState == STOPPED. Does nothing otherwise.
     * @post m_globalState == STARTED
     */
    FWSERVICES_API SharedFutureType start();

    /**
     * @brief Invoke stopping() if m_globalState == STARTED. Does nothing otherwise. Stops all observations.
     *
     * @post m_globalState == STOPPED
     *
     */
    FWSERVICES_API SharedFutureType stop();

    /**
     * @brief Invoke updating() if m_globalState == STARTED. Does nothing otherwise.
     * @pre m_globalState == STARTED
     */
    FWSERVICES_API SharedFutureType update();

    /**
     * @brief Associate the service to another object
     * @param[in] _obj change association service from m_associatedObject to _obj
     * @pre m_globalState == STARTED
     * @pre m_associatedObject != _obj
     * @deprecated Use getAutoConnections() instead
     *
     * This method provides to associate the service to another object without stopping
     * and deleting it. Furthermore, this method modify all observations to be aware to
     * _obj notifications.
     *
     *
     */
    FWSERVICES_API SharedFutureType swap( ::fwData::Object::sptr _obj );

    /**
     * @brief Associate the service to another object
     * @param[in] _obj change association service from m_associatedObject to _obj
     * @pre m_globalState == STARTED
     * @pre m_associatedObject != _obj
     *
     * This method provides to associate the service to another object without stopping
     * and deleting it. Furthermore, this method modify all observations to be aware to
     * _obj notifications.
     *
     *
     */
    FWSERVICES_API SharedFutureType swapKey( const KeyType& _key, ::fwData::Object::sptr _obj );
    //@}

    /**
     * @name All concerning status access
     */

    //@{

    /**
     * @brief Return the global process status
     * @return m_globalState
     */
    FWSERVICES_API GlobalStatus getStatus() const throw();

    /**
     * @brief Test if the service is started or not
     * @return true if m_globalState == STARTED
     */
    FWSERVICES_API bool isStarted() const throw();

    /**
     * @brief Test if the service is stopped or not
     * @return true if m_globalState == STOPPED
     */
    FWSERVICES_API bool isStopped() const throw();

    /**
     * @brief Return the configuration process status
     * @return m_configurationState
     */
    FWSERVICES_API ConfigurationStatus getConfigurationStatus() const throw();

    /**
     * @brief Return the update process status
     * @return m_updatingState
     */
    FWSERVICES_API UpdatingStatus getUpdatingStatus() const throw();
    //@}


    /**
     * @name All concerning configuration
     */

    //@{

    /**
     * @brief Return the configuration, in an xml format read using runtime library
     * @return m_configuration, a structure which represents the service configuration
     */
    FWSERVICES_API ::fwRuntime::ConfigurationElement::sptr getConfiguration() const;

    /**
     * @brief Return the configuration, in an boost property tree
     */
    FWSERVICES_API ConfigType getConfigTree() const;


//    /**
//     * @brief Check the configuration using XSD if possible
//     * @return true if the configuration is validate or if
//     * there is not XSD available to validate the configuration.
//     */
//    FWSERVICES_API bool checkConfiguration() ;


    //@}


    /**
     * @name Optimized access to associated Object & Helper
     */
    //@{

    /**
     * @brief Return the object associated to service
     * @return m_associatedObject
     * @pre the service must have an associated object set
     * @pre associated object has not expired
     * @deprecated use getInput() or getInOut() instead
     */
    FWSERVICES_API ::fwData::Object::sptr getObject();

    /**
     * @brief Return the object associated to service. The object is casted.
     * @return m_associatedObject casted in a good type
     * @pre the service must have an associated object set
     * @pre associated object does not be expired
     * @post cast verification in debug mode ( assertion on dynamic cast )
     * @deprecated use getInput() or getInOut() instead
     */
    template< class DATATYPE > SPTR(DATATYPE) getObject();

    /**
     * @brief Return the inputs map associated to service
     * @return m_inputsMap
     * @pre the service must have an associated object set
     * @pre associated objects have not expired
     */
    FWSERVICES_API const InputMapType& getInputs() const;

    /**
     * @brief Return the inouts map associated to service
     * @return m_inoutsMap
     * @pre the service must have an associated object set
     * @pre associated objects have not expired
     */
    FWSERVICES_API const OutputMapType& getInOuts() const;

    /**
     * @brief Return the objects associated to service
     * @return m_associatedObject
     * @pre the service must have an associated object set
     * @pre associated objects have not expired
     */
    FWSERVICES_API std::vector< ::fwData::Object::csptr > getObjects() const;

    /**
     * @brief Return the input object at the given key. Asserts if the data is not of the right type.
     * @param key name of the data to retrieve.
     * @return object cast in the right type, nullptr if not found.
     * @pre the service must have an associated object set.
     * @post cast verification in debug mode ( assertion on dynamic cast ).
     */
    template< class DATATYPE > CSPTR(DATATYPE) getInput(const KeyType &key) const;

    /**
     * @brief Return the inout object at the given key. Asserts if the data is not of the right type.
     * @param key name of the data to retrieve.
     * @return object cast in the right type, nullptr if not found.
     * @pre the service must have an associated object set.
     * @post cast verification in debug mode ( assertion on dynamic cast ).
     */
    template< class DATATYPE > SPTR(DATATYPE) getInOut(const KeyType &key) const;

    /**
     * @brief Return the input object at the given key. Asserts if the data is not of the right type.
     * @param key name of the data to retrieve.
     * @return object cast in the right type, nullptr if not found.
     * @pre the service must have an associated object set.
     * @post cast verification in debug mode ( assertion on dynamic cast ).
     */
    template< class DATATYPE > CSPTR(DATATYPE) getInput(const KeyType &keybase, size_t index) const;

    /**
     * @brief Return the inout object at the given key. Asserts if the data is not of the right type.
     * @param key name of the data to retrieve.
     * @return object cast in the right type, nullptr if not found.
     * @pre the service must have an associated object set.
     * @post cast verification in debug mode ( assertion on dynamic cast ).
     */
    template< class DATATYPE > SPTR(DATATYPE) getInOut(const KeyType &keybase, size_t index) const;

    /**
     * @brief Register an output object at a given key in the OSR, replacing it if it already exists.
     * @param key name of the data or the group to register.
     * @param object pointer to the object to register.
     * @param index optional index of the key in the case of a member of a group of keys.
     */
    FWSERVICES_API void setOutput(const ::fwServices::IService::KeyType& key, const ::fwData::Object::sptr& object,
                                  size_t index = 0);

    /**
     * @brief Return the number of key in a group of keys.
     * @param keybase group name.
     * @return number of keys in this group.
     */
    size_t getKeyGroupSize(const KeyType& keybase) const;
    //@}

    /**
     * @name Communication connection between object::signals and service::slots
     */
    //@{

    typedef ::fwServices::helper::SigSlotConnection::KeyConnectionsType KeyConnectionsType;

    /**
     * @brief This class is a helper to define the connections of a service and its data.
     */
    class KeyConnectionsMap
    {
    public:
        void push (const KeyType& key,
                   const ::fwCom::Signals::SignalKeyType& sig,
                   const ::fwCom::Slots::SlotKeyType& slot)
        {
            m_keyConnectionsMap[key].push_back(std::make_pair(sig, slot));
        }

        typedef std::map< KeyType, KeyConnectionsType> KeyConnectionsMapType;

        KeyConnectionsMapType::const_iterator find(const KeyType& key) const
        {
            return m_keyConnectionsMap.find(key);
        }
        KeyConnectionsMapType::const_iterator end() const
        {
            return m_keyConnectionsMap.cend();
        }
        bool empty() const
        {
            return m_keyConnectionsMap.empty();
        }
        size_t size() const
        {
            return m_keyConnectionsMap.size();
        }

    private:
        std::map< KeyType, KeyConnectionsType> m_keyConnectionsMap;
    };

    /**
     * @brief Returns proposals to connect service slots to associated objects signals,
     * this method is used for obj/srv auto connection
     */
    FWSERVICES_API virtual KeyConnectionsMap getAutoConnections() const;

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     * @deprecated Use getAutoConnections() instead
     */
    FWSERVICES_API virtual KeyConnectionsType getObjSrvConnections() const;

    //@}

    /**
     * @name Misc
     */

    //@{

    /**
     * @brief Streaming a service
     * @see IService::operator<<(std::ostream & _ostream, IService& _service)
     * @note Invoke IService::info( std::ostream )
     */
    FWSERVICES_API friend std::ostream& operator<<(std::ostream& _sstream, IService& _service);

    /** Set/get the version of the service. Temporary, this should be removed when appXml is gone. */
    FWSERVICES_API static void setVersion(int version);
    FWSERVICES_API static bool isVersion2();

    /**
     * @brief Return the id of the object, throw if it is not found
     */
    FWSERVICES_API IdType getObjectId(const KeyType& _key) const;

    /**
     * @brief Set the id of an object key
     */
    FWSERVICES_API void setObjectId(const KeyType& _key, const IdType& _id);
    //@}

protected:

    /**
     * @name Constructor and Destructor
     */

    //@{

    /**
     * @brief IService constructor.
     *
     * This constructor does nothing. By default, m_associatedObject is null and
     * service is considered as STOPPED, NOTUPDATING and UNCONFIGURED.
     */
    FWSERVICES_API IService();

    /**
     * @brief IService desctructor.
     *
     * This destructor does nothing.
     */
    FWSERVICES_API virtual ~IService();

    //@}

    /**
     * @name Interface to override (implementation contract)
     */

    //@{

    /**
     * @brief Initialize the service activity.
     *
     * Use configuration to start his job. For example : the start method
     * installs a button in a frame and show the frame.
     * @see start()
     */
    FWSERVICES_API virtual void starting() throw ( ::fwTools::Failed ) = 0;

    /**
     * @brief Uninitialize the service activity. The stop() method is always invoked before destroying a service.
     *
     * @see stop()
     */
    FWSERVICES_API virtual void stopping() throw ( ::fwTools::Failed ) = 0;

    /**
     * @brief Swap the service from associated object to another object
     * @see swap()
     * @todo This method must be pure virtual
     * @todo FIXME after code update for all services
     * @todo This method must have in parameter the new object or the old ?
     * @deprecated use swapping(const KeyType& key) instead
     */
    virtual void swapping() throw ( ::fwTools::Failed )
    {
    }

    /**
     * @brief Swap the service from an associated object to another object.
     * The key in parameter indicates allows to retrieve the new data with getInput(), getInOut() or getOutput().
     * If you need the old object, you need to keep a shared pointer on it inside your service implementation.
     *
     * @param key of the object
     * @see swapKey()
     * @todo This method must be pure virtual
     * @todo This method must have in parameter the new object or the old ?
     */
    virtual void swapping(const KeyType& key) throw ( ::fwTools::Failed )
    {
    }

    /**
     * @brief Configure the service before starting. Apply the configuration to service.
     * @see configure()
     */
    FWSERVICES_API virtual void configuring() throw ( ::fwTools::Failed ) = 0;

    /**
     * @brief Reconfigure the service activity when is started.
     * @todo This method should be pure virtual
     * @see configure()
     */
    FWSERVICES_API virtual void reconfiguring() throw ( ::fwTools::Failed );

    /**
     * @brief Perform some computations according to object (this service is attached to) attribute values and its internal state.
     * @see update()
     */
    FWSERVICES_API virtual void updating() throw ( ::fwTools::Failed ) = 0;

    /**
     * @brief Write information in a stream.
     *
     * This method is used by operator<<(std::ostream & _sstream, IService& _service)
     * to avoid declaration of << by all services.
     */
    FWSERVICES_API virtual void info( std::ostream& _sstream );

    //@}

    /**
     * @brief Configuration element used to configure service internal state using a generic XML like structure
     */
    ::fwRuntime::ConfigurationElement::sptr m_configuration;

    /**
     * @brief associated object of service
     * @todo this field must be private
     */
    ::fwData::Object::wptr m_associatedObject;


    /**
     * @name Slot API
     */
    //@{

    /// Slot to call start method
    StartSlotType::sptr m_slotStart;

    /// Slot to call stop method
    StopSlotType::sptr m_slotStop;

    /// Slot to call update method
    UpdateSlotType::sptr m_slotUpdate;

    /// Slot to call swap method
    SwapSlotType::sptr m_slotSwap;

    /// Slot to call swap method
    SwapKeySlotType::sptr m_slotSwapKey;

    /// Associated worker
    SPTR(::fwThread::Worker) m_associatedWorker;

    //@}

private:

    /**
     * @brief associated inputs of the service ordered by key
     */
    InputMapType m_inputsMap;

    /**
     * @brief associated input/outputs of the service ordered by key
     */
    OutputMapType m_inOutsMap;

    /**
     * @brief associated outputs of the service ordered by key
     */
    OutputMapType m_outputsMap;

    /**
     * @brief associated objects of the service ordered by key
     */
    std::map<KeyType, IdType> m_idsMap;

    /**
     * @brief size of key groups if they exist
     */
    std::map<std::string, size_t> m_keyGroupSize;

    /**
     * @brief Defines the current global status of the service.
     */
    GlobalStatus m_globalState;

    /**
     * @brief Defines if the service is updating.
     */
    UpdatingStatus m_updatingState;

    /**
     * @brief Defines if the service is configured or not.
     */
    ConfigurationStatus m_configurationState;

    /**
     * @brief Defines if the service is part of a version 1 or a version 2 application.
     */
    static int s_version;

};

} // namespace fwServices

#include "fwServices/IService.hxx"

#endif // __FWSERVICES_ISERVICE_HPP__
