/*!
 * \file model.h
 * \brief Storage logic
 *
 * \author Alexey Erunovskiy
 * \date June 2023
 */

#pragma once

#include <iostream>
#include <memory>
#include <map>
#include <string>

#include "window_interface.h"

/*!
 * \namespace model
 * \brief Contain data storage object
 */
namespace model
{

/*!
 * \struct Shape
 * \brief All shapes parent class
 */
struct Shape
{
    /*!
     * \brief Shape constructor
     * \param name Shape name
     */
    explicit Shape(const std::string& name) : name_(name) {}

    //! Shape destructor
    virtual ~Shape() = default;

    /*!
     * \brief Get name of this shape
     * @return Shape name
     */
    std::string get_name() const
    {
        return name_;
    }

protected:
    std::string name_;
};

/*!
 * \struct Rectangle
 * \brief Rectangle shape
 */
struct Rectangle : Shape
{
    /*!
     * \brief Rectangle constructor
     * \param name Rectangle name
     */
    explicit Rectangle(const std::string& name) : Shape(name) {}
};

/*!
 * \struct Ellipse
 * \brief Ellipse shape
 */
struct Ellipse : Shape
{
    /*!
    * \brief Ellipse constructor
    * \param name Ellipse name
    */
    explicit Ellipse(const std::string& name) : Shape(name) {}
};

/*!
 * \struct Line
 * \brief Line shape
 */
struct Line : Shape
{
    /*!
    * \brief Line constructor
    * \param name Line name
    */
    explicit Line(const std::string& name) : Shape(name) {}
};

/*!
 * \class Document
 * \brief Document model
 */
class Document
{
public:
    /*!
     * \brief Document modle constructor
     * \param window Shared pointer of UI
     */
    explicit Document(const std::shared_ptr<view::IWindow>& window) : window_(window){}

    /*!
     * \brief Document modle constructor
     * \param window Shared pointer of UI
     * \param path Import path
     */
    Document(const std::shared_ptr<view::IWindow>& window, const std::string& path) : window_(window){}

    /*!
     * \brief Export document
     * @param path Export path
     */
    void export_data(const std::string& path)
    {
        std::string message;
        message = "Export document to " + path;
        emit(message);
    }

    /*!
     * \brief Imitation of shape adding
     * @param shape Some shape
     */
    void add_shape(const std::shared_ptr<Shape>& shape)
    {
        std::cout << "Add " << shape->get_name() << " shape" << std::endl;
        shapes_[shape_number++] = shape;
    }

    /*!
     * \brief Imitation of shape removing
     * @param shape_id Some shape ID
     */
    void remove_shape(size_t shape_id)
    {
        std::string message;
        if (shapes_.find(shape_id) != shapes_.end())
        {
            shapes_.erase(shape_id);
            message = "Erase shape with id = " + std::to_string(shape_id);
        }
        else
        {
            message = "Shape with id = " + std::to_string(shape_id) + " is not exists\n";
        }

        emit(message);
    }

    /*!
     * \brief Execute UI update
     * \param message Output message
     */
    void emit(const std::string& message)
    {
        window_->update(message);
    }

private:
    //! Shapes map
    std::map<size_t, std::shared_ptr<Shape>> shapes_;

    //! Last shape ID
    size_t shape_number {0};

    //! Shared pointer to UI
    std::shared_ptr<view::IWindow> window_;
};

}