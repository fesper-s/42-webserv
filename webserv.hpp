#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <unistd.h>
# include <cstdlib>
# include <fstream>
# include <sstream>
# include <vector>
# include <map>

//system
# include <sys/stat.h>
# include <sys/socket.h>


//network
# include <netinet/in.h>
# include <arpa/inet.h>

//files
# include "Parser.hpp"
# include "ConfigFile.hpp"
# include "ServerConfig.hpp"
# include "utils.hpp"

# define MAX_CONTENT_LENGTH 30000000

#endif
