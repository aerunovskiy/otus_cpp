#include "cmd_worker.h"
#include "logger.h"

#include <vector>

int main (int argc, char** argv)
{
    try
    {
        if(argc <= 1)
            return 0 ;

        auto app_name = std::filesystem::path( argv[0] ).filename().string();

        CmdWorker cmd( app_name);
        cmd.run(argc, argv);

    }
    catch(const std::exception &e)
    {
        Logger::get().log_error(e.what()) ;
    }

    return 0;
}

