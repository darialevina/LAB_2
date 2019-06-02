cmake_minimum_required (VERSION 3.8)

project(sorting)
set(SOURCE_LIB sorting.cpp sorting.def)
add_library(sorting SHARED ${SOURCE_LIB})
set_source_files_properties(sorting.def PROPERTIES HEADER_FILE_ONLY TRUE)