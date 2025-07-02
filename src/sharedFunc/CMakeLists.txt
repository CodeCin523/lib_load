set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -rdynamic")

add_library(libSharedFunc SHARED lib.c)

add_executable(appSharedFunc main.c)