file(GLOB Sources *.cpp *.h)
add_library(log-file MODULE ${Sources})
target_link_libraries(log-file win32support common-log)
