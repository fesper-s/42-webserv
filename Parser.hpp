#ifndef PARSER_HPP
# define PARSER_HPP

#include "webserv.hpp"

class Parser {
    public:
        Parser();
        ~Parser();
        
        int checkAndReadFile(const std::string &config_file);

        std::string removeFileComments(std::string &content);
        std::string removeFileWhiteSpace(std::string &content);
    private:
        //size_t  _nb_server;
};

#endif