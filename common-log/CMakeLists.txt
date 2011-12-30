file(GLOB Sources *.cpp *.h ../include/despoof/common-log/*.h)
add_library(common-log STATIC ${Sources})
