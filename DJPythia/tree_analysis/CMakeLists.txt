add_library(djpythia_tree_analysis tree_reader.h d_meson_qa.cc d_meson_qa.h)

target_include_directories(djpythia_tree_analysis
        INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(djpythia_tree_analysis PUBLIC ROOT::Hist)

target_compile_features(djpythia_tree_analysis PRIVATE cxx_std_14)

target_compile_options(djpythia_tree_analysis
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)