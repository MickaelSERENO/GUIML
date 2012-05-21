cmake_minimum_required(VERSION 2.6)
project(GUIML)
set(LIBRARY_OUTPUT_PATH lib)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
include_directories(${sfml_include_dir} include)
link_directories(${sfml_link_dir})

file(
	GLOB_RECURSE
	sources_files
	src/*
	include/*
	)

add_library(
	GUIML
	SHARED
	STATIC
	${sources_files}
	)

target_link_libraries(
	GUIML
	${sfml_system_lib_name}
	)

target_link_libraries(
	GUIML
	${sfml_window_lib_name}
	)


target_link_libraries(
	GUIML
	${sfml_graphics_lib_name}
	)


target_link_libraries(
	GUIML
	${sfml_audio_lib_name}
	)
