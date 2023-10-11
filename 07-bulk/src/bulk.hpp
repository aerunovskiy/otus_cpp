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

        std::cout << "bulk: ";

        while ( !commands.empty() )
        {

            std::cout << commands.front();

            commands.pop();

            if ( !commands.empty() )
                std::cout << ", ";
        }

        std::cout << std::endl;
    }
    

    private:

    std::queue<std::string> commands;
    std::stack<std::string> timepoints;

    size_t brackets_balance {0};

    size_t commands_number;
};