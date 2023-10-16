#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <stack>


class Bulk final
{
    public:

    explicit Bulk(size_t cmd_num) : commands_number(cmd_num) {}

    void push_back(const std::string& cmd)
    {
        if ( cmd.compare("{") == 0 || commands.empty())
            timepoints.push(get_timestamp());

        if ( cmd.compare("{") == 0 )
        {
             if ( brackets_balance == 0 )
                print();

            ++brackets_balance;

            return;
        }

        if ( cmd.compare("}") == 0 )
        { 
            --brackets_balance;

            if (brackets_balance == 0) 
                print();
                
            return;
        }

        if ( cmd.compare("EOF") == 0 && brackets_balance == 0 )
        {
            print();

            return;
        }

        commands.push(cmd);
        
        if ( commands.size() >= commands_number && brackets_balance == 0 )
            print();
    }

    void print()
    {
        if (commands.empty())
            return;

        std::string out = "bulk: ";

        while ( !commands.empty() )
        {

            out += commands.front();

            commands.pop();

            if ( !commands.empty() )
                out += ", ";
        }

        out += "\n";

        std::cout << out;

        std::ofstream log ("bulk_" + timepoints.front() + ".log");

        timepoints.pop();

        if (!log.is_open())
            std::cerr << "Failed to open log file for writing" << std::endl;

        log << out;

        log.close();
    }
    

    private:

    std::string get_timestamp() const 
    {
        return std::to_string(time(nullptr));
    }

    std::queue<std::string> commands;
    std::queue<std::string> timepoints;

    size_t brackets_balance {0};

    size_t commands_number;
};