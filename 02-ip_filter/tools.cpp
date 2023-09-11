#include "tools.h"

#include "version.h"

namespace tools
{

int version() {
    return PROJECT_VERSION_PATCH;
}

std::vector<std::string> split(const std::string &str, char delimiter) {
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delimiter);

    while(stop != std::string::npos) {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(delimiter, start);
    }

    r.push_back(str.substr(start));

    return r;
}

}