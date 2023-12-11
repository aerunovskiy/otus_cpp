
cmake_minimum_required( VERSION 3.10 FATAL_ERROR )

project( test_bayan LANGUAGES CXX )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage" )

enable_testing()

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)

find_package(Boost REQUIRED COMPONENTS
        program_options
        filesystem
        regex
        )

add_executable( ${PROJECT_NAME}
        ${CMAKE_CURRENT_SOURCE_DIR}/test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_bayan.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_files.cpp
        ../src/bayan.cpp
        )

target_link_libraries(${PROJECT_NAME}
        GTest::gtest
        Boost::program_options
        Boost::filesystem
        Boost::regex
        )

