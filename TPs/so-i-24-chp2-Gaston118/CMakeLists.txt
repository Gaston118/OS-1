cmake_minimum_required(VERSION 3.22)

project(
    "myshell"
    VERSION 1.0
    DESCRIPTION "PROPERTY OF VAULT TEC CORP"
)

set(CMAKE_C_STANDARD 17)

include(CTest)
include_directories(include)
include_directories(test)

find_package(cJSON REQUIRED)
find_package(unity REQUIRED)

add_executable(${PROJECT_NAME} src/main.c)
add_executable(test1 test/test1.c)

target_link_libraries(${PROJECT_NAME} PRIVATE cjson::cjson)
target_link_libraries(test1 PRIVATE unity::unity cjson::cjson)

target_include_directories(test1 PRIVATE include so-i-24-chp2-Gaston118/include)

add_test(NAME test1 COMMAND test1)

if(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Coverage enabled")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} --coverage")
endif()

add_custom_target(
    coverage
    COMMAND lcov --capture --directory . --output-file coverage.info --exclude '../TPs/*'
    COMMAND genhtml coverage.info --output-directory coverage
    COMMAND xdg-open coverage/index.html
    DEPENDS test1
    COMMENT "Generando cobertura de código"
)

add_dependencies(coverage test1)