aux_source_directory(./ SOURCE)
add_executable(DotProjection ${SOURCE})

target_link_libraries(DotProjection sfml-system sfml-graphics sfml-window)
target_include_directories(DotProjection PUBLIC "../third_party/SFML/include")