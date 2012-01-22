if(WIN32)
	set(Platform_Sources_Dir src/Win32)
else()
	set(Platform_Sources_Dir src/Posix)
endif()

file(GLOB Sources src/*.cpp src/*.h)
file(GLOB Platform_Sources ${Platform_Sources_Dir}/*.cpp ${Platform_Sources_Dir}/*.h)

add_library(unittest-cpp STATIC ${Sources} ${Platform_Sources})
