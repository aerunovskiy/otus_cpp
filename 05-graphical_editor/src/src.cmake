# \authors Alexey Erunovskiy
# \date May 2023

if ( NOT SRC_INCLUDED )

    set( SRC_INCLUDED TRUE )

    include_directories( ${CMAKE_CURRENT_LIST_DIR} )

    include( ${CMAKE_CURRENT_LIST_DIR}/model/model.cmake )
    include( ${CMAKE_CURRENT_LIST_DIR}/view/view.cmake )
    include( ${CMAKE_CURRENT_LIST_DIR}/controller/controller.cmake )

    set( SRC
         ${MODEL}
         ${VIEW}
         ${CONTROLLER} )

endif()