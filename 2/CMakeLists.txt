
cmake_minimum_required(VERSION 3.16)

# название проекта (обязательно)
project(test)

# установка стандарта языка - C++20
set(CMAKE_CXX_STANDARD 20)

add_compile_options(--coverage)
add_link_options(--coverage)
# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

				set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D SIMP -Wall -Wextra -g")
				add_library(simple_class domino/simple_class.h domino/simple_class.cpp)
				link_libraries(simple_class)
				message("SIMPLE\n")

                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DIF_D -Wall -Wextra -g")
                #add_library(simple_class domino/simple_class.h domino/simple_class.cpp)
                add_library(difficult_class_dynamic domino/difficult_class_dynamic.h domino/difficult_class_dynamic.cpp)
                link_libraries(simple_class)
                link_libraries(difficult_class_dynamic)
                message("DUFFICULT DYNAMIC\n")
   
                set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D DIF_S -Wall -Wextra -g")
                #set_target_properties(oopprog2 PROPERTIES OUTPUT_NAME "dif_static")
                #add_library(simple_class simple_class.h simple_class.cpp)
                add_library(difficult_class_static domino/difficult_class_static.h domino/difficult_class_static.cpp)
                link_libraries(simple_class)
                link_libraries(difficult_class_static)
                message("DIFICULT STATIC\n")
              
       
        

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
# ищем в системе пакет Catch2 для тестирования
# необходимо предварительно установить через пакетный менеджер (напр. sudo apt install catch2),
# или скачать из гит-репозитория https://github.com/catchorg/Catch2
find_package(Catch2 2 REQUIRED)

# создание исполняемого файла для программы тестирования
add_executable(testing testing.cpp)

# подключение библиотек circle и Catch2 к тесту
target_link_libraries(testing simple_class difficult_class_static difficult_class_dynamic Catch2::Catch2)
