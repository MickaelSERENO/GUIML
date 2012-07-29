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
	${sources_files}
	)

add_library(
	GUIMLStatic
   	STATIC
	${sources_files}
	)

#target link for the .so
target_link_libraries(
	GUIML
	${sfml_system_lib_name}
	${sfml_window_lib_name}
	${sfml_graphics_lib_name}
	${sfml_audio_lib_name}
	)

#target link for the .a
target_link_libraries(
	GUIMLStatic
	${sfml_system_lib_name}
	${sfml_window_lib_name}
	${sfml_graphics_lib_name}
	${sfml_audio_lib_name}
	)

set_target_properties(GUIMLStatic PROPERTIES OUTPUT_NAME GUIML)
set(sfml_include_dir "/usr/include" CACHE FILEPATH "Où se situe le Dossier SFML")
set(sfml_link_dir "/usr/lib" CACHE FILEPATH "Où se situe les lib SFML dynamique")
set(sfml-system_lib_name "sfml-system" CACHE STRING "Le nom de la lib system de la sfml")
set(sfml-window_lib_name "sfml-window" CACHE STRING "Le nom de la lib window de la sfml")
set(sfml-graphics_lib_name "sfml-graphics" CACHE STRING "Le nom de la lib graphics de la sfml")
set(sfml-audio_lib_name "sfml-audio" CACHE STRING "Le nom de la lib audio de la sfml")
