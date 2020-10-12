# Library with the base classes
add_library(djp_tree_analysis SHARED
        include/tree_reader.h
        src/d_meson_qa.cc include/d_meson_qa.h
        src/analysis_manager.cc include/analysis_manager.h
        src/task.cc include/task.h)

target_link_libraries(djp_tree_analysis PUBLIC ROOT::Hist)

target_compile_features(djp_tree_analysis PRIVATE cxx_std_14)

target_compile_options(djp_tree_analysis
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)

# Library with the user defined Tasks
add_library(djp_user_tree_analysis SHARED src/task_d.cc include/task_d.h)

target_link_libraries(djp_user_tree_analysis
        PUBLIC djp_tree_analysis djp_data_model)

target_link_libraries(djp_user_tree_analysis PUBLIC ROOT::Hist)

target_compile_features(djp_user_tree_analysis PRIVATE cxx_std_14)

target_compile_options(djp_user_tree_analysis
        PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)