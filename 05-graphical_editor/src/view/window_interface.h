/*!
 * \author Alexey Erunovskiy
 * \file windows_interface.h
 * \brief Interface for connect controller and view
 */

#pragma once

#include <string>

/*!
 * \namespace view
 * \brief Contain user interface classes
 */
namespace view
{

/*!
 * \class IWindow
 * \brief Pseudo window form interface
 */
class IWindow
{
public:
    //! Interface virtual destructor
    virtual ~IWindow() = default;

    /*!
     * \brief Message print
     * \param message Output text
     */
    virtual void update(const std::string& message) const = 0;
};

}
