cmake_minimum_required(VERSION 3.23)
project(lab3)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Entity)
#add_subdirectory(tests)
# установка флагов компилятора: CMAKE_CXX_FLAGS += -Wall -Wextra
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")
add_compile_options(-fsanitize=thread -g)
add_link_options(-fsanitize=thread)
add_executable(game main.cpp )
target_link_libraries(game Entity)


# ищем в системе пакет Catch2 для тестирования
# необходимо предварительно установить через пакетный менеджер (напр. sudo apt install catch2),
# или скачать из гит-репозитория https://github.com/catchorg/Catch2
#find_package(Catch2 2 REQUIRED)
#include_directories(${LIB_DIR}/Catch)
# создание исполняемого файла для программы тестирования
#add_executable(tests tests/testing.cpp)

# подключение библиотек circle и Catch2 к тесту
#target_link_libraries(tests Catch2::Catch2)

