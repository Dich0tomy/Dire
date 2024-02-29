add_executable( dire "main.cpp" )

target_compile_features(dire INTERFACE cxx_std_20)

target_include_directories(dire PRIVATE ".")

target_link_libraries(dire PRIVATE libdire fmt)
