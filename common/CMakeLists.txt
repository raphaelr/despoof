file(GLOB Sources *.cpp *.h)
add_library(common STATIC ${Sources})
target_link_libraries(common win32support)
