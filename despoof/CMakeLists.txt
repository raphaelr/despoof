file(GLOB Sources *.cpp *.h ${Despoof_includes}/despoof/*.h ${Despoof_includes}/despoof/import/*.h)
add_executable(despoof ${Sources})
add_executable(despoof-svc ${Sources})

set_target_properties(despoof PROPERTIES COMPILE_DEFINITIONS BUILD_DEFAULT)
set_target_properties(despoof-svc PROPERTIES COMPILE_DEFINITIONS BUILD_SERVICE)

set(Despoof_libs common win32support argtable2)
target_link_libraries(despoof ${Despoof_libs})
target_link_libraries(despoof-svc ${Despoof_libs})
