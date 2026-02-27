# Если gtest установлен в системе
find_package(GTest REQUIRED)
include(GoogleTest)

set(LIBS ${PROJECT_NAME} GTest::gtest_main)

set(TEST_SOURCES
    test_foo.cpp
)

foreach(TEST_FILE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_FILE_NAME ${TEST_FILE} NAME_WE)
    set(EXECUTABLE_NAME ${TEST_FILE_NAME})
    add_executable(${EXECUTABLE_NAME} ${TEST_FILE})
    target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${LIBS})
    gtest_discover_tests(${EXECUTABLE_NAME})
endforeach()