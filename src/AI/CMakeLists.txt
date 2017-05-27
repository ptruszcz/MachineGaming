file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

add_library(pyvolution SHARED ${SOURCES})

set_target_properties(pyvolution PROPERTIES PREFIX "")

add_custom_command(TARGET pyvolution POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:pyvolution> ${TEST_DIR}#./../../test/AI
        )