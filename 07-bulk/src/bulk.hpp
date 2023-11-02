#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <stack>

#include "observer.hpp"

class Bulk final
{
    public:

    explicit Bulk(size_t cmd_num) : commands_number(cmd_num) {}

    void add_observer(Observer* observer)
    {
        observers.push_back(observer);
    }

    void remove_observer(Observer* observer)
    {
        observers.erase(std::remove_if(observers.begin(), observers.end(), 
            [observer](Observer* o)
            {
                return observer == o;
            }), observers.end());
    }

    void notify(const std::string& message)
    {
        for (auto observer : observers)
             observer->update(message);
    }

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

        ConsoleLogObserver console(std::cout);
        add_observer(&console);

        FileLogObserver file("bulk_" + timepoints.front() + ".log");
        add_observer(&file);

        notify(out);

        remove_observer(&file);

        timepoints.pop();
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

    std::vector<Observer*> observers;
};