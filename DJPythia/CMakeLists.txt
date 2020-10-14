cmake_minimum_required(VERSION 3.11)
project(DJPythia VERSION 1.0.0
                 DESCRIPTION "Simulations of D meson excited states PYTHIA8"
                 LANGUAGES CXX)

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
add_subdirectory(djp_data_model)
add_subdirectory(djp_generator)
add_subdirectory(djp_analysis)
add_subdirectory(dpj_cli)


