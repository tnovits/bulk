
#include "FileSubscriber.h"
#include "CoutSubscriber.h"
#include "CommandPackage.h"


int main()
{
    auto blockCommandCount = 0;
    std::string command;

    std::cin >> blockCommandCount;

    auto commandPackage = std::make_shared<CommandPackage>(blockCommandCount);

    auto fileSubscriber = std::make_shared<FileSubscriber>();
    auto coutSubscriber = std::make_shared<CoutSubscriber>();

    commandPackage->addSubscriber(fileSubscriber);
    commandPackage->addSubscriber(coutSubscriber);

    std::getline(std::cin, command);
    while( std::getline(std::cin, command) )
    {
        commandPackage->addCommand(command);
    }

    commandPackage->update();

    return 0;
}