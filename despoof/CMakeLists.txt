file(GLOB Sources *.cpp *.h ${Despoof_includes}/*.h)
add_executable(despoof ${Sources})
target_link_libraries(despoof win32support yaml-cpp)
