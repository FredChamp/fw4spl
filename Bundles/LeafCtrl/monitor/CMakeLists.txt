project(monitor VERSION 0.1)

set(PRIVATE_LINKS
    fwCore
    fwTools
    fwData
    fwGui
    fwMemory
    fwRuntime 
    fwServices
)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    #TODO write FindDbgHelp ...
    list(APPEND dbghelp)
endif()

add_target()
