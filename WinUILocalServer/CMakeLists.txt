add_executable(WinUILocalServer "src/main.cpp")

target_link_libraries(WinUILocalServer WinUILib)
target_include_directories(WinUILocalServer PUBLIC "${CMAKE_SOURCE_DIR}/WinUI/include")
set_target_properties(WinUILocalServer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/WinUILocalServer)