add_executable(djpythia_generate src/generate.cc)
target_link_libraries(djpythia_generate PUBLIC djp_generator djp_data_model
                      ROOT::Tree ROOT::RIO Boost::program_options)

target_compile_features(djpythia_generate PRIVATE cxx_std_14)
target_compile_options(djpythia_generate PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)