add_executable(WinUILocalSocket "src/main.cpp")

target_link_libraries(WinUILocalSocket WinUILib)
target_include_directories(WinUILocalSocket PUBLIC "${CMAKE_SOURCE_DIR}/WinUI/include")
set_target_properties(WinUILocalSocket PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/WinUILocalSocket VS_DEBUGGER_ENVIRONMENT "PATH=${CMAKE_SOURCE_DIR}/lib/$<CONFIG>;%PATH%")