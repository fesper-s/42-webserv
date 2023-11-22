#ifndef CGIPANEL_HPP
#define CGIPANEL_HPP

#include "Webserv.hpp"

class LocateFile;
class Request;
class CgiPanel {
 private:
  std::map<std::string, std::string> env;
  char **chEnv;
  char **argv;
  int exitStatus;
  std::string cgiPath;
  pid_t cgiPid;

 public:
  int pipeIn[2];
  int pipeOut[2];

  CgiPanel();
  CgiPanel(std::string path);
  ~CgiPanel();
  CgiPanel(CgiPanel const &other);
  CgiPanel &operator=(CgiPanel const &rhs);
  void initEnv(Request &req, const std::vector<LocateFile>::iterator it_loc);
  void initEnvCgi(Request &req, const std::vector<LocateFile>::iterator it_loc);
  void execute(short &error_code);
  void clear();
  void setContentLength(int length);
  void setContentType(const std::string &contentType);
  void setDefaultEnvValues(Request &req, std::string cgiExec);
  void setRequestHeaders(Request &req);
  void createChEnv();
  void createArgv(const std::string &cgiExec);
  unsigned int fromHexToDec(const std::string &nb);
  void closePipes();
  void setCgiPath(const std::string &cgiPath);
  const pid_t &getCgiPid() const;
  const std::string &getCgiPath() const;
  std::string getPathInfo(std::string &path, std::vector<std::string> extensions);
  int findStart(const std::string path, const std::string delim);
  std::string decode(std::string &path);
};

#endif
