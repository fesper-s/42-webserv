#ifndef PARSER_HPP
# define PARSER_HPP

#include "webserv.hpp"

class Parser {
    public:
        Parser();
        ~Parser();
        
        int checkAndReadFile(const std::string &config_file);

        std::string removeFileComments(std::string &content);
        void removeFileWhiteSpace(std::string &content);
        void splitServer(std::string &content);
        size_t findStartServer(size_t start, std::string &content);
		size_t findEndServer(size_t start, std::string &content);

        class ErrorException : public std::exception {
			private:
				std::string _message;
			public:
				ErrorException(std::string message) throw() {
					_message = "CONFIG PARSER ERROR: " + message;
				}
				virtual const char* what() const throw() {
					return (_message.c_str());
				}
				virtual ~ErrorException() throw() {}
		};
    private:
        //std::vector<ServerConfig> _servers;
        std::vector<std::string> _server_config;
        size_t _nb_server;
};

#endif
