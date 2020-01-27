#pragma once

#include "ISubscriber.h"
#include <iostream>
#include <tuple>


class CoutSubscriber final : public ISubscriber
{
public:
    CoutSubscriber() = default;
    virtual ~CoutSubscriber() = default;

    void update( std::time_t blockTime, std::vector<std::string>& data ) override
    {
        std::ignore = blockTime;

        std::cout << "bulk: ";

        for (auto command = data.cbegin(); command != data.cend(); ++command)
        {
            if (command != data.cbegin())
            {
                std::cout << ", ";
            }

            std::cout << *command;
        }

        std::cout << std::endl;
    }
};