#pragma once

#include <ctime>
#include <vector>
#include <string>

class ISubscriber
{
public:
    ISubscriber() = default;
    virtual ~ISubscriber() = default;

    virtual void update( std::time_t blockTime, std::vector<std::string>& data ) = 0;
};