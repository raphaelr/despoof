file(GLOB Sources *.cpp *.h)
add_library(nw-sendarp MODULE ${Sources})
target_link_libraries(nw-sendarp win32support iphlpapi)
