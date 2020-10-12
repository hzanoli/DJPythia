
root_generate_dictionary(G__djpythia_data_model
                         event.h particle.h d_meson.h
                         LINKDEF data_model_linkdef.h)

add_library(djpythia_data_model SHARED
            G__djpythia_data_model.cxx
            event.cc event.h
            particle.cc particle.h
            d_meson.cc d_meson.h
            origin.h)

target_include_directories(djpythia_data_model
                           PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_compile_features(djpythia_data_model
                        PRIVATE cxx_std_14)

target_compile_options(djpythia_data_model
                       PRIVATE -O2 -pedantic -W -Wall -Wshadow -fPIC)