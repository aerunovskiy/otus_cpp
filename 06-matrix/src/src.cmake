# \authors Alexey Erunovskiy
# \date May 2023

if ( NOT SRC_INCLUDED )

    set( SRC_INCLUDED TRUE )

    include_directories( ${CMAKE_CURRENT_LIST_DIR} )

    include(${CMAKE_CURRENT_LIST_DIR}/sparse_matrix/sparse_matrix.cmake)

    set( SRC
         ${MATRIX} )

endif()