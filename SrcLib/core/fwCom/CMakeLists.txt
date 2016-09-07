cmake_minimum_required( VERSION 3.1 )

project(fwCom VERSION 0.1)

set(PRIVATE_LINKS
    fwCore
)

set(PUBLIC_LINKS
    fwThread
)

add_target()