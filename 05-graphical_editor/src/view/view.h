/*!
 * \file view.h
 * \brief  User Interface
 *
 * \author Alexey Erunovskiy
 * \date June 2023
 */

#pragma once

#include <cstdint>
#include <memory>
#include <string>

#include "window_interface.h"
#include "model.h"
#include "controller.h"

/*!
 * \namespace view
 * \brief Contain user interface classes
 */
namespace view
{

/*!
 * \class Window
 * \brief Pseudo window form class
 */
class Window : public IWindow
{
public:
    /*!
     * \brief Window constructor
     *
     * \param width Window width
     * \param height Window height
     */
    Window(uint width, uint height) : width_(width), height_(height) {}

    /*!
     * \brief Create controller exemplar for work with empty document
     * @return Controller shared pointer
     */
    std::shared_ptr<controller::Controller> create_document()
    {
        return std::make_shared<controller::Controller>(this);
    }

    /*!
     * \brief Create controller exemplar for work with imported document
     * @return Controller shared pointer
     */
    std::shared_ptr<controller::Controller> import_document(const std::string& path)
    {
        return std::make_shared<controller::Controller>(this, path);
    }

    /*!
     * \brief Message print
     * \param message Output text
     */
    void update(const std::string& message) const override
    {
        std::cout << message << std::endl;
    }

private:
    //! Window width
    uint width_;
    //! Window height
    uint height_;
};

/*!
 * \class UI
 * \brief User Interface
 * \details Fake user interface elements creator
 */
class UI
{
public:
    /*!
     * \brief Create pseudo window form
     * @return Window shared pointer
     */
    static std::shared_ptr<Window> create_window()
    {
        return std::make_shared<Window>(800, 600); // For example
    }
};

};
