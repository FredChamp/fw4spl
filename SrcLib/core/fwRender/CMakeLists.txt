project(fwRender VERSION 0.1)

set(PUBLIC_LINKS
    fwGui
)

set(PRIVATE_LINKS
    fwCore
    fwGui
    fwRuntime
    fwServices
    fwTools
)

add_target()