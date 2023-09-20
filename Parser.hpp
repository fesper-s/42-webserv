#ifndef PARSER_HPP
# define PARSER_HPP

#include "Webserv.hpp"

class Parser
{
    public:
        Parser();
        ~Parser();
        
        int checkAndReadFile(const std::string &config_file);
};

#endif