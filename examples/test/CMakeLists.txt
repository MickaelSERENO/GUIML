cmake_minimum_required(VERSION 2.6)
project(test)
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x")
set(EXECUTABLE_OUTPUT_PATH bin)
include_directories(../../include
	${sfml_dir_include})
link_directories(${guiml_dir_lib}
	${sfml_dir_lib})

set(sfml_dir_include "/usr/include" CACHE PATH "Où se situe le Dossier SFML")
set(sfml_dir_lib "/usr/lib" CACHE PATH "Où se situe les lib SFML dynamique")
set(sfml_system_lib "sfml-system" CACHE STRING "Le nom de la lib system de la sfml")
set(sfml_window_lib "sfml-window" CACHE STRING "Le nom de la lib window de la sfml")
set(sfml_audio_lib "sfml-audio" CACHE STRING "Le nom de la lib audio de la sfml")
set(sfml_graphics_lib "sfml-graphics" CACHE STRING "Le nom de la lib graphics de la sfml")
set(guiml_dir_lib "../../lib" CACHE PATH "Chemin vers les lib de GUIML")

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

