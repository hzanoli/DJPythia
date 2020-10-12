add_library(djpythia_generator generator.cc generator.h)

target_include_directories(djpythia_generator
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           PUBLIC ${PYTHIA8_INCLUDE_DIR})

target_compile_features(djpythia_generator PRIVATE cxx_std_14)
target_compile_options(djpythia_generator
                       PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)

target_link_libraries(djpythia_generator "${PYTHIA8_LIBRARIES}")

target_compile_options(djpythia_generator
                       PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)