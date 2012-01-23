file(GLOB Sources *.cpp *.h)
add_executable(win32support_test ${Sources} ../main.cpp)
target_link_libraries(win32support_test win32support unittest-cpp)
