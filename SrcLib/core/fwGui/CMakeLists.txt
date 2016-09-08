project(fwGui VERSION 0.1)

set(PRIVATE_LINKS
    fwCore
    fwData
    fwRuntime
    fwServices
    fwTools
    fwCom
    fwThread

)
set(PUBLIC_LINKS
    fwLog
)

add_target()

