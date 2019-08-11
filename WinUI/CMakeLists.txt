include(GenerateExportHeader)

file(GLOB_RECURSE lib_includes "src/*.h")
file(GLOB_RECURSE lib_sources "src/*.cpp")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(WinUI_lib SHARED ${lib_includes} ${lib_sources})
generate_export_header(WinUI_lib)