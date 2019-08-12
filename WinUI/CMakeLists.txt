include(GenerateExportHeader)

file(GLOB_RECURSE lib_includes "src/*.h")
file(GLOB_RECURSE lib_sources "src/*.cpp")

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
add_library(WinUILib SHARED ${lib_includes} ${lib_sources})
generate_export_header(WinUILib EXPORT_FILE_NAME ${CMAKE_BINARY_DIR}/exports/winui_export.h)

target_link_libraries(WinUILib user32.lib)
target_include_directories(WinUILib PUBLIC ${CMAKE_BINARY_DIR}/exports)

set_target_properties(WinUILib PROPERTIES TARGET_LIBRARY_OUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
get_target_property(lib_path WinUILib TARGET_LIBRARY_OUT_DIRECTORY)
set_target_properties(WinUILib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${lib_path} LIBRARY_OUTPUT_DIRECTORY ${lib_path} RUNTIME_OUTPUT_DIRECTORY ${lib_path})