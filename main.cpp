
#include "FileSubscriber.h"
#include "CoutSubscriber.h"
#include "CommandPackage.h"


int main(int argc, char *argv[])
{
    auto blockCommandCount = 0;
    std::string command;

    if( argc > 1 )
    {
        blockCommandCount =  std::atoi(argv[1]);
    }
    else
    {
        blockCommandCount = 5;
    }

    auto commandPackage = std::make_shared<CommandPackage>(blockCommandCount);

    auto fileSubscriber = std::make_shared<FileSubscriber>();
    auto coutSubscriber = std::make_shared<CoutSubscriber>();

    commandPackage->addSubscriber(fileSubscriber);
    commandPackage->addSubscriber(coutSubscriber);

    while( std::getline(std::cin, command) )
    {
        commandPackage->addCommand(command);
    }

    commandPackage->update();

    return 0;
}