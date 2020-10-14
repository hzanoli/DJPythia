add_executable(djpythia_generate src/generate.cc)

target_link_libraries(djpythia_generate PUBLIC djp_generator djp_data_model
        ROOT::Tree ROOT::RIO Boost::program_options)

target_include_directories(djpythia_generate
        PUBLIC ${PYTHIA8_INCLUDE_DIR} $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(djpythia_generate PRIVATE cxx_std_14)
target_compile_options(djpythia_generate PRIVATE
        -O2 -pedantic -W -Wall -Wshadow -fPIC)


add_executable(djpythia_analyse src/analyse.cc)

target_link_libraries(djpythia_analyse PUBLIC djp_tree_analysis djp_data_model
        djp_user_tree_analysis ROOT::Tree ROOT::RIO Boost::program_options ${PYTHIA8_LIBRARIES})

target_include_directories(djpythia_analyse
        PUBLIC ${PYTHIA8_INCLUDE_DIR} $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_features(djpythia_analyse PRIVATE cxx_std_14)
target_compile_options(djpythia_generate PRIVATE
        -O2 -pedantic -W -Wall -Wshadow -fPIC)