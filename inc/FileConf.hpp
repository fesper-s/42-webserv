#ifndef FILECONG_HPP
#define FILECONG_HPP

#include "Webserv.hpp"

enum FileType {
  FILE_TYPE = 1,
  DIRECTORY_TYPE = 2,
  OTHER_TYPE = 3,
  INVALID_TYPE = -1,
};

class FileConf {
 private:
  std::string path;

 public:
  FileConf();
  FileConf(std::string const path);
  ~FileConf();

  static int getTypePath(std::string const path);
  static int checkAccessFile(std::string const path, int mode);
  std::string readFile(std::string path);
  static int isFileExistAndReadable(std::string const path, std::string const index);
};

#endif
