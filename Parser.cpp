#include "Parser.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

int Parser::checkAndReadFile(const std::string &config_file)
{
    std::string content;
    ConfigFile file(config_file);

    if (file.getTypePath(file.getPath()) != 1)
        std::cout << "file is invalid" << std::endl;
    if (file.checkFile(file.getPath(), 4) == -1)
        std::cout << "file is invalid" << std::endl;
    content = file.readFile(config_file);
        
}
