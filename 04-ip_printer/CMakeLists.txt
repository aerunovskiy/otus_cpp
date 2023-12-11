cmake_minimum_required(VERSION 3.12)

cmake_policy( SET CMP0079 NEW )

set(PATCH_VERSION "1" CACHE INTERNAL "Patch tools")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(04_ip_printer VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} main.cpp tools.cpp)

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    add_executable(ip_printer_tests tests.cpp)

    set_target_properties(tests PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(tests
            GTest::GTest
            GTest::Main
    )
endif()

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT alexey.erunovskiy@gmail.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    add_test(tests tests)
endif()