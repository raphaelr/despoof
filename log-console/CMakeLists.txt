file(GLOB Sources *.cpp *.h)
add_library(log-console MODULE ${Sources})
target_link_libraries(log-console common-log)
