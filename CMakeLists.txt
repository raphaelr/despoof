cmake_minimum_required(VERSION 2.8)
project(despoof CXX)

set(Despoof_includes "${PROJECT_SOURCE_DIR}/include")
set(Argtable2_includes "${PROJECT_SOURCE_DIR}/vendor/argtable2/src")
set(Output_directory "${CMAKE_BINARY_DIR}")

include_directories(${Despoof_includes} ${Argtable2_includes})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Output_directory})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Output_directory})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Output_directory})

add_subdirectory(vendor)

add_subdirectory(log-console)
add_subdirectory(log-file)
add_subdirectory(nw-sendarp)
add_subdirectory(win32support)
add_subdirectory(despoof)
