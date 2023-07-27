/*!
 * \file controller.h
 * \brief Business logic
 *
 * \author Alexey Erunovskiy
 * \date June 2023
 */

#pragma once

#include "model.h"
#include "window_interface.h"

/*!
 * \namespace controller
 * \brief Contain objects for data manipulation
 */
namespace controller
{

/*!
 * \class Controller
 * \brief Business logic implementation
 */
class Controller
{
public:
    /*!
     * \brief Controller constructor
     * \param window UI
     */
    explicit Controller(view::IWindow* window)
    : window_(window)
    {
        document_ = std::make_shared<model::Document>(window_);
    }

    /*!
     * \brief Controller constructor with exported file
     * \param window UI
     * \param path Export path
     */
    Controller(view::IWindow* window, const std::string& path)
    : window_(window)
    {
        document_ = std::make_shared<model::Document>(window_);
    }

    /*!
     * \brief Execute document export
     * @param export_path Export path
     */
    void export_document(const std::string& export_path)
    {
        document_->export_data(export_path);
    }

    /*!
     * \brief Add ellipse shape
     */
    void add_ellipse()
    {
        document_->add_shape(std::make_shared<model::Ellipse>("Ellipse1"));
    }

    /*!
     * \brief Add rectangle shape
     */
    void add_rectangle()
    {
        document_->add_shape(std::make_shared<model::Rectangle>("Rectangle1"));
    }

    /*!
     * \brief Add line shape
     */
    void add_line()
    {
        document_->add_shape(std::make_shared<model::Line>("Line1"));
    }

    /*!
     * \brief Remove shape from document
     * @param shape_id ID of removing shape
     */
    void remove_shape(size_t shape_id)
    {
        document_->remove_shape(shape_id);
    }

private:
    //! Shared pointer to UI
    std::shared_ptr<view::IWindow> window_;

    //! Shared pointer to model
    std::shared_ptr<model::Document> document_;
};

}