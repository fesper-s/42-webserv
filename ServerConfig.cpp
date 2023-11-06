#include "ServerConfig.hpp"

ServerConfig::ServerConfig() {
	this->_port = 0;
	this->_host = 0;
	this->_server_name = "";
	this->_root = "";
	this->_client_max_body_size = MAX_CONTENT_LENGTH;
	this->_index = "";
	this->_listen_fd = 0;
	this->_autoindex = false;
	this->initErrorPages();
}

ServerConfig::~ServerConfig() {}

ServerConfig::ServerConfig(const ServerConfig &other) {
	if (this != &other) {
		this->_server_name = other._server_name;
		this->_root = other._root;
		this->_host = other._host;
		this->_port = other._port;
		this->_client_max_body_size = other._client_max_body_size;
		this->_index = other._index;
		this->_error_pages = other._error_pages;
		this->_listen_fd = other._listen_fd;
		this->_autoindex = other._autoindex;
		this->_server_address = other._server_address;
	}
	return ;
}

ServerConfig &ServerConfig::operator=(const ServerConfig & rhs) {
	if (this != &rhs) {
		this->_server_name = rhs._server_name;
		this->_root = rhs._root;
		this->_port = rhs._port;
		this->_host = rhs._host;
		this->_client_max_body_size = rhs._client_max_body_size;
		this->_index = rhs._index;
		this->_error_pages = rhs._error_pages;
		this->_listen_fd = rhs._listen_fd;
		this->_autoindex = rhs._autoindex;
		this->_server_address = rhs._server_address;
	}
	return (*this);
}

void ServerConfig::initErrorPages(void) {
	_error_pages[301] = "";
	_error_pages[302] = "";
	_error_pages[400] = "";
	_error_pages[401] = "";
	_error_pages[402] = "";
	_error_pages[403] = "";
	_error_pages[404] = "";
	_error_pages[405] = "";
	_error_pages[406] = "";
	_error_pages[500] = "";
	_error_pages[501] = "";
	_error_pages[502] = "";
	_error_pages[503] = "";
	_error_pages[505] = "";
	_error_pages[505] = "";
}

void ServerConfig::setServerName(std::string serverName) {
    checkToken(serverName);
    this->_server_name = serverName;
}

void ServerConfig::setHost(std::string parametr) {
	checkToken(parametr);
	if (parametr == "localhost")
		parametr = "127.0.0.1";
    //verifica se o endereço IP é valido usando inet_pton para formata-lo em binário
	if (!isValidHost(parametr)) {
        std::cout << "Wrong syntax: host" << std::endl;
        exit(EXIT_FAILURE);
    }
	this->_host = inet_addr(parametr.data());
}

void ServerConfig::setRoot(std::string root) {
	checkToken(root);
	if (ConfigFile::getTypePath(root) == 2) {
		this->_root = root;
		return ;
	}
	char dir[1024];
	getcwd(dir, 1024);
	std::string full_root = dir + root;
	if (ConfigFile::getTypePath(full_root) != 2) {
		std::cout << "Wrong syntax: root" << std::endl;
        exit(EXIT_FAILURE);
    }
	this->_root = full_root;
}

void ServerConfig::setFd(int fd) {
	this->_listen_fd = fd;
}

void ServerConfig::setPort(std::string parametr) {
	unsigned int port;
	
	port = 0;
	checkToken(parametr);
	for (size_t i = 0; i < parametr.length(); i++) {
		if (!std::isdigit(parametr[i])) {
			std::cout << "Wrong syntax: port" << std::endl;
            exit(EXIT_FAILURE);
        }
	}
	port = ft_stoi((parametr));
	if (port < 1 || port > 65636) {
		std::cout << "Wrong syntax: port" << std::endl;
        exit(EXIT_FAILURE);
    }
	this->_port = (uint16_t) port;
}

bool ServerConfig::isValidHost(std::string host) const
{
	struct sockaddr_in sockaddr;
  	if (inet_pton(AF_INET, host.c_str(), &(sockaddr.sin_addr)))
        return true;
    else
        return false;
}

void ServerConfig::checkToken(std::string &parametr)
{
	size_t pos = parametr.rfind(';');
	if (pos != parametr.size() - 1)
	{   
        std::cout << "Invalid token" << std::endl;
        exit(EXIT_FAILURE);
    }
	parametr.erase(pos);
}