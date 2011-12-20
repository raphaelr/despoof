file(GLOB Sources *.cpp *.h)
add_executable(despoof-svctool ${Sources})
target_link_libraries(despoof-svctool common win32support argtable2)
