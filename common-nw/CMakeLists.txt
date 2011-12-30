file(GLOB Sources *.cpp *.h ../include/despoof/common-nw/*.h)
add_library(common-nw STATIC ${Sources})
target_link_libraries(common-nw win32support iphlpapi)
