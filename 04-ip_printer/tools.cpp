/*!
 * \file tools.cpp
 * \brief Implementation of secondary functions
 * \author Alexey Erunovskiy
 */
#include "tools.h"

#include "version.h"

namespace tools {

int version() {
    return PROJECT_VERSION_PATCH;
}

}