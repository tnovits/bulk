#pragma once

#include "ISubscriber.h"
#include <fstream>

class FileSubscriber final : public ISubscriber
{
public:
    FileSubscriber() = default;
    virtual ~FileSubscriber() = default;


    void update( std::time_t blockTime, std::vector<std::string>& data ) override
    {
        std::string fileName = "bulk" + std::to_string(blockTime) + ".log";

        std::fstream fs;

        fs.open(fileName, std::ios::out);

        if(fs.is_open())
        {
            for( const auto& command : data )
            {
                fs << command << "\n";
            }

            fs.close();
        }
    }
};
