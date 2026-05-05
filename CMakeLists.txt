cmake_minimum_required(VERSION 3.28.3) 

project(parallel_integrate)			

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    src/main.cpp
    src/Communicator.cpp
    src/Manager.cpp
    src/Solver.cpp
)

add_executable(main ${SOURCES})

target_include_directories(main
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)			

find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

add_library(muparser SHARED IMPORTED)
set_property(TARGET muparser PROPERTY
             IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/muparser/build/libmuparser.so)

target_link_libraries(main muparser)
target_include_directories(main PUBLIC ${PROJECT_SOURCE_DIR}/muparser/include/)