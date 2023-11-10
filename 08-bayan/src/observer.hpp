#pragma once

#include <string>

class Observer
{
public:
    virtual void update(const std::string& message) = 0;
};

class ConsoleLogObserver : public Observer
{
public:
    explicit ConsoleLogObserver(std::ostream& stream) : stream(stream) {};

    void update(const std::string& message) override
    {
        stream << message;
    }

private:
     std::ostream& stream;
};

class FileLogObserver : public Observer
{
public:
    explicit FileLogObserver(const std::string& file_path) : file_path(file_path) {};

    void update(const std::string& message) override
    {
        std::ofstream file_log (file_path);

        if (!file_log.is_open())
            std::cerr << "Failed to open log file for writing" << std::endl;

        file_log << message;

        file_log.close();
    }

private:
    std::string file_path;
};