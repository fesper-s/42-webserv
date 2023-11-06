#include "ConfigFile.hpp"

ConfigFile::ConfigFile() {}

ConfigFile::ConfigFile(std::string const path): _path(path) {}

ConfigFile::~ConfigFile() {}

std::string ConfigFile::getPath() {
	return (this->_path);
}

int ConfigFile::getTypePath(std::string const path) {
	struct stat	buffer; //struct que contem st_mode
	int			result;
	
	result = stat(path.c_str(), &buffer); //funçao stat preenche a estrutura buffer
	if (result == 0) {
		if (buffer.st_mode & S_IFREG) //se st_mode for S_IFREG, então é um arquivo regular
			return (1);
		else if (buffer.st_mode & S_IFDIR) //se for S_IFDIR é um diretório
			return (2);
		else
			return (3);
	}
	else
		return (-1);
}

int	ConfigFile::checkFile(std::string const path, int mode) {
	return (access(path.c_str(), mode));
}

std::string	ConfigFile::readFile(std::string path) {
	if (path.empty() || path.length() == 0)
		return (NULL);
	std::ifstream config_file(path.c_str());
	if (!config_file || !config_file.is_open())
		return (NULL);

	std::stringstream stream_binding;
	stream_binding << config_file.rdbuf(); //copia todo conteudo do arquivo para a string
	return (stream_binding.str());
}


int ConfigFile::isRealAndReadable(std::string const path, std::string const index) {
	if (getTypePath(index) == 1 && checkFile(index, 4) == 0)
		return (0);
	if (getTypePath(path + index) == 1 && checkFile(path + index, 4) == 0)
		return (0);
	return (-1);
}
