cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GTEST "Whether to build Google test" ON)

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME}_cli main.cpp)
add_library(${PROJECT_NAME} lib.cpp)

set_target_properties(${PROJECT_NAME}_cli ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(${PROJECT_NAME} PRIVATE
        "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME}_cli PRIVATE
        ${PROJECT_NAME}
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(test_version test_version.cpp)

    set_target_properties(test_version PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(test_version PROPERTIES
            COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
            INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(test_version
            ${Boost_LIBRARIES}
            ${PROJECT_NAME}
    )
endif()

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    add_executable(gtest_version gtest_version.cpp)

    set_target_properties(gtest_version PROPERTIES
            CXX_STANDARD 14
            CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(gtest_version
            GTest::GTest
            GTest::Main
            ${PROJECT_NAME}
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME}_cli PRIVATE
            /W4
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
    )

    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
                /W4
        )
    endif()

    if(WITH_GTEST)
        target_compile_options(gtest_version PRIVATE
                /W4
        )
    endif()
else()
    target_compile_options(${PROJECT_NAME}_cli PRIVATE
            -Wall -Wextra -pedantic -Werror
    )

    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )

    if(WITH_BOOST_TEST)
        target_compile_options(test_version PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif()

    if(WITH_GTEST)
        target_compile_options(gtest_version PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ${PROJECT_NAME}_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT alexey.erunovskiy@gmail.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(test_version test_version)
endif()

if(WITH_GTEST)
    enable_testing()
    add_test(gtest_version gtest_version)
endif()