add_library(djp_generator SHARED src/generator.cc
        include/djp_generate/generator.h
        src/pythia_analysis.cc include/djp_generate/pythia_analysis.h)

target_include_directories(djp_generator
        PUBLIC ${PYTHIA8_INCLUDE_DIR} $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(djp_generator PRIVATE cxx_std_14)
target_compile_options(djp_generator
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)

target_link_libraries(djp_generator PUBLIC ${PYTHIA8_LIBRARIES} djp_data_model)

target_compile_options(djp_generator PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)