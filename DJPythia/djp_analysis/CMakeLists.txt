# Library with the base classes
add_library(djp_tree_analysis STATIC
        include/djp_analysis/tree_reader.h
        src/analysis_manager.cc include/djp_analysis/analysis_manager.h
        src/task.cc include/djp_analysis/task.h)

target_include_directories(djp_tree_analysis
        PUBLIC $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_link_libraries(djp_tree_analysis PUBLIC djp_data_model ROOT::Tree
                      PUBLIC ROOT::Hist PUBLIC ROOT::TreePlayer)

target_compile_features(djp_tree_analysis PRIVATE cxx_std_14)

target_compile_options(djp_tree_analysis
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)

# Library with the user defined Tasks
add_library(djp_user_tree_analysis STATIC src/task_d.cc include/djp_analysis/task_d.h)

target_link_libraries(djp_user_tree_analysis
        PUBLIC djp_tree_analysis djp_data_model)

target_link_libraries(djp_user_tree_analysis PUBLIC ROOT::Hist)

target_compile_features(djp_user_tree_analysis PRIVATE cxx_std_14)

target_compile_options(djp_user_tree_analysis
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)