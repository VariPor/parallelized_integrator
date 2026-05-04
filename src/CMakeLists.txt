
cmake_minimum_required(VERSION 3.28.3) 

project(parallel_integrate)			

set(SOURCE_EXE main.cpp)		

add_library(muparser SHARED IMPORTED)
set_property(TARGET muparser PROPERTY
             IMPORTED_LOCATION /home/var/c_plus_plus/parallel_calc/parallel_calc/muparser/build/libmuparser.so)

add_executable(main ${SOURCE_EXE})

target_link_libraries(main muparser)
target_include_directories(main PUBLIC /home/var/c_plus_plus/parallel_calc/parallel_calc/muparser/include/)