#ifndef CONFIGFILE_HPP
# define CONFIGFILE_HPP

#include "Webserv.hpp"

class ConfigFile
{
    public:
        ConfigFile();
        ConfigFile(std::string const path);
        ~ConfigFile();

        std::string getPath();
        int getTypePath(std::string const path);

		int checkFile(std::string const path, int mode);
		std::string	readFile(std::string path);
		int isRealAndReadable(std::string const path, std::string const index);
    private:
        _path;
};

#endif