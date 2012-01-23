file(GLOB Sources *.cpp *.h)
add_executable(common_test ${Sources} ../main.cpp)
target_link_libraries(common_test common unittest-cpp)
