cmake_minimum_required(VERSION 3.11)
project(DJPythia VERSION 1.0.0)

set(CMAKE_BUILD_TYPE Debug)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
list(APPEND CMAKE_PREFIX_PATH "/root-cern/root/cmake")
set(PYTHIA8_ROOT_DIR /pythia/pythia8)

#include BOOST
find_package(Boost 1.71 COMPONENTS program_options REQUIRED)

# Include ROOT
find_package(ROOT 6.22 REQUIRED)
include(${ROOT_USE_FILE})

#include PYTHIA
find_package(Pythia8 REQUIRED)

add_subdirectory(data_model)
add_subdirectory(generator)
add_subdirectory(pythia_analysis)
add_subdirectory(tree_analysis)

add_executable(djpythia main.cc)
target_link_libraries(djpythia PUBLIC djpythia_generator djpythia_data_model
                      djpythia_pythia_analysis "${PYTHIA8_LIBRARIES}"
                      ROOT::Tree ROOT::RIO Boost::program_options)

target_compile_features(djpythia PRIVATE cxx_std_14)
target_compile_options(djpythia PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)




