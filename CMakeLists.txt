cmake_minimum_required(VERSION 3.24)
project(cmake_example)

option(WITH_TESTS "enable tests" OFF)

# Тип библиотеки определяется опцией cmake "BUILD_SHARED_LIBS"
# По умолчанию STATIC
add_library(${PROJECT_NAME})

add_subdirectory(src)

# Для включения тестов нужно вызвать команду cmake с опцией -DWITH_TESTS=ON
if(WITH_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()