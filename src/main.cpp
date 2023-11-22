#include "../inc/ServerConf.hpp"
#include "../inc/Webserv.hpp"

int error(std::string errorMessage) {
  std::cerr << "\033[0;31m";
  std::cerr << errorMessage << std::endl;
  std::cerr << "\033[0m";
  return 1;
}

int main(int argc, char **argv) {
  try {
    if (argc != 1 && argc != 2)
      throw std::invalid_argument("Invalid number of arguments. Usage: ./webserv <config_file>.conf.");
    signal(SIGPIPE, SIG_IGN);
    std::string FileConf;
    if (argc == 2)
      FileConf = (argv[1]);
    else
      FileConf = "config/default.conf";
    Parser serverParser;
    ServerConf managerServ;
    serverParser.parseServerFileConf(FileConf);
    managerServ.setupServers(serverParser.getServers());
    managerServ.processServerRequests();
  } catch (std::exception &err) {
    return error(err.what());
  }
  return 0;
}