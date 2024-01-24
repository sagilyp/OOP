# установка версии CMake
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(oopprog2)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

find_package(Doxygen REQUIRED dot OPTIONAL_COMPONENTS mscgen dia)

option(DIF_S OFF)
option(DIF_D OFF)
option(SIMP OFF)
	if (DIF_D)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DIF_D -Wall -Wextra -g")
		add_library(simple_class simple_class.h simple_class.cpp)
		add_library(difficult_class_dynamic difficult_class_dynamic.h difficult_class_dynamic.cpp)
		link_libraries(simple_class)
		link_libraries(difficult_class_dynamic)
		message("DUFFICULT DYNAMIC\n")
		add_executable(dif_d main.cpp)
	endif(DIF_D)	
	if (DIF_S)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DIF_S -Wall -Wextra -g")
		#set_target_properties(oopprog2 PROPERTIES OUTPUT_NAME "dif_static")
		add_library(simple_class simple_class.h simple_class.cpp)
		add_library(difficult_class_static difficult_class_static.h difficult_class_static.cpp)
		link_libraries(simple_class)
		link_libraries(difficult_class_static)		
		message("DIFICULT STATIC\n")
		add_executable(dif_s main.cpp)
	endif(DIF_S)	
	if (SIMP)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D SIMP -Wall -Wextra -g")
		add_library(simple_class simple_class.h simple_class.cpp)
		link_libraries(simple_class)
		message("SIMPLE\n")
		add_executable(simp main.cpp)
	endif(SIMP)	


#doxygen_add_docs(../simple_class.cpp ../difficult_class_static.cpp ../difficult_class_dynamic.cpp)
#set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/..)
#set(DOXYGEN_IN simple_class.cpp difficult_class_static.cpp difficult_class_dynamic.cpp)
#set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR})

#configure_file(simple_class.cpp difficult_class_static.cpp difficult_class_dynamic.cpp @ONLY)
#message("Doxygen build started")
#add_custom_target(doc_doxygen ALL_COMMAND ${DOXYGEN_EXECUTABLE})
#ADD_DOCUMENTATION(doc Doxyfile)

#SET(DOXY_INPUT ${PROJECT_SOURCE_DIR})
#ADD_DOCUMENTATION(doc Doxyfile)
set(DOXYGEN_GENERATE_HTML YES)
doxygen_add_docs(docs simple_class.cpp difficult_class_static.cpp difficult_class_dynamic.cpp @ONLY)
#DOXYGEN_GENERATE_HTML(docs)

