file(GLOB SOURCES
        "*.h"
        "*.cc"
        "*.hpp"
        )

add_library(EvolutionaryAlgorithm_Ext SHARED ${SOURCES})

set_target_properties(EvolutionaryAlgorithm_Ext PROPERTIES PREFIX "")