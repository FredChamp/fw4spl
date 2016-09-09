project(Tuto01Basic VERSION 0.1)  # Name of the application) and version of the application

set(PRIVATE_LINKS
    dataReg # to load the data registry
    servicesReg # to load the service registry
    gui # to load gui
    guiQt # to load qt implementation of gui
    fwlauncher # executable to run the application
    appXml2 # to parse the application configuration
)

# Set the configuration to use : 'tutoBasicConfig'
bundleParam(appXml2 PARAM_LIST config PARAM_VALUES tutoBasicConfig) 

add_target() # create a cmake target
