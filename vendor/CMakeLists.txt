# Disable the "install" command
macro(install)
endmacro(install)

add_subdirectory(argtable2)

set_directory_properties(PROPERTIES COMPILE_DEFINITIONS _CRT_SECURE_NO_WARNINGS)
set_target_properties(argtable2 PROPERTIES COMPILE_FLAGS "/W2")
