/*!
 * \file main.cpp
 * \brief Entry app file
 *
 * \author Alexey Erunovskiy
 * \date May 2023
 */

#include <iostream>

#include "view.h"

/*!
 * \brief Entry point
 *
 * Execution of the program starts here.
 *
 * \param[in] argc Number of arguments.
 * \param[in] argv List of arguments.
 *
 * \return App exit status.
 */
int main(int, char**)
{
    auto main_window = view::UI::create_window();

    auto doc1 = main_window->create_document();
    std::string path {"/tmp/doc2.xml"};
    auto doc2 = main_window->import_document(path);

    doc1->add_ellipse();
    doc2->add_rectangle();
    doc1->add_line();

    doc1->remove_shape(1);
    doc2->remove_shape(0);

    std::string export_path{"/tmp/doc1.xml"};
    doc1->export_document(export_path);

    return EXIT_SUCCESS;
}