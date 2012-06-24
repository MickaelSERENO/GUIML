cmake_minimum_required(VERSION 2.6)
project(test)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
set(EXECUTABLE_OUTPUT_PATH bin)
include_directories(../../include
	${sfml_dir_include})
link_directories(../../lib
	${sfml_dir_lib})

file(
	GLOB_RECURSE
	sources_files
	src/*
	)

add_executable(
	test
	${sources_files}
	)

target_link_libraries(
	test
	GUIML
	${sfml_system_lib}
	${sfml_window_lib}
	${sfml_audio_lib}
	${sfml_graphics_lib}
	)
