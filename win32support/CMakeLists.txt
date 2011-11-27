file(GLOB Sources *.cpp *.h ${Despoof_includes}/win32/*.h)
add_library(win32support STATIC ${Sources})
