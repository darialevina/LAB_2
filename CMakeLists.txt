cmake_minimum_required (VERSION 3.8)

project(LAB_2)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

set(SOURCE_EXE main.cpp)

set(PROJ_IO      io     )
set(PROJ_SORTING sorting)

include_directories(${PROJ_IO}     )
include_directories(${PROJ_SORTING})

add_executable (lab_2 ${SOURCE_EXE})

add_subdirectory(${PROJ_IO}     )
add_subdirectory(${PROJ_SORTING})

target_link_libraries(lab_2 ${PROJ_IO} gtestd)
