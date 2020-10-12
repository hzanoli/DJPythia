
root_generate_dictionary(G__djp_data_model
        include/djp_data_model/event.h include/djp_data_model/particle.h
        include/djp_data_model/d_meson.h
        LINKDEF include/djp_data_model/data_model_linkdef.h)


add_library(djp_data_model SHARED
        G__djp_data_model.cxx
        src/event.cc include/djp_data_model/event.h
        src/particle.cc include/djp_data_model/particle.h
        src/d_meson.cc include/djp_data_model/d_meson.h
        include/djp_data_model/origin.h)

target_include_directories(djp_data_model PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


target_compile_features(djp_data_model PRIVATE cxx_std_14)

target_compile_options(djp_data_model PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)