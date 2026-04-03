find_package(GTest REQUIRED)

file(GLOB_RECURSE TEST_SOURCES test_*.cpp)

foreach (TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME run_${TEST_FILE_NAME})
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
    target_compile_options(${EXECUTABLE_NAME} PRIVATE -Werror -Wall -Wextra -pedantic -Wshadow -Wconversion -Wsign-conversion)
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${PROJECT_NAME} GTest::gtest_main)
    add_test(NAME ${EXECUTABLE_NAME} COMMAND ${EXECUTABLE_NAME})
endforeach ()