add_library(djpythia_pythia_analysis pythia_analysis.cc pythia_analysis.h)

target_include_directories(djpythia_pythia_analysis
                           INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
                           PUBLIC ${PYTHIA8_INCLUDE_DIR})

target_link_libraries(djpythia_pythia_analysis
                      djpythia_data_model "${PYTHIA8_LIBRARIES}")

target_compile_features(djpythia_pythia_analysis PRIVATE cxx_std_14)

target_compile_options(djpythia_pythia_analysis
                       PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)