file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

add_library(pyvolution SHARED ${SOURCES})

set_target_properties(pyvolution PROPERTIES PREFIX "")