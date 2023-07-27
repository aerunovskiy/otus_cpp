cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch tools")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(allocator VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build Google test" ON)

include_directories(${CMAKE_CURRENT_LIST_DIR})

configure_file(version.h.in version.h)

add_executable(${PROJECT_NAME} main.cpp)
add_library(tools tools.cpp)

set_target_properties(${PROJECT_NAME} tools PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(tools PRIVATE
        "${CMAKE_BINARY_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        tools
)

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    add_executable(tests tests.cpp)

    set_target_properties(tests PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(tests
            GTest::GTest
            GTest::Main
            tools
    )
endif()

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE
            /W4
    )

    target_compile_options(tools PRIVATE
            /W4
    )

    if(WITH_GTEST)
        target_compile_options(tests PRIVATE
                /W4
        )
    endif()
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
            -Wall -Wextra -pedantic -Werror
    )

    target_compile_options(tools PRIVATE
            -Wall -Wextra -pedantic -Werror
    )

    if(WITH_GTEST)
        target_compile_options(tests PRIVATE
                -Wall -Wextra -pedantic -Werror
        )
    endif()
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