#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

int Parser::checkAndReadFile(const std::string &config_file) {
    std::string content;
    ConfigFile file(config_file);

    if (file.getTypePath(file.getPath()) != 1)
        throw ErrorException("file is invalid");
    if (file.checkFile(file.getPath(), 4) == -1)
        throw ErrorException("file is invalid");
    content = file.readFile(config_file);
    if (content.empty())
		throw ErrorException("File is empty");

    content = removeFileComments(content);
    removeFileWhiteSpace(content);
    splitServer(content);

    return (0);
}

std::string Parser::removeFileComments(std::string &content) {
    std::string result;
    std::istringstream iss(content);
    std::string line;

    while (std::getline(iss, line)) {
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            line.erase(commentPos);
        }
        result += line + "\n";
    }
    return result;
}

void Parser::removeFileWhiteSpace(std::string &content) {
	size_t i = 0;

	while (content[i] && isspace(content[i]))
		i++;
	content = content.substr(i);
	i = content.length() - 1;
	while (i > 0 && isspace(content[i]))
		i--;
	content = content.substr(0, i + 1);
}

void Parser::splitServer(std::string &content) {
    size_t start = 0;
	size_t end = 1;

	if (content.find("server", 0) == std::string::npos)
		throw ErrorException("Server did not find");
	while (start != end && start < content.length())
	{
		start = findStartServer(start, content);
		end = findEndServer(start, content);
		if (start == end)
			throw ErrorException("problem with scope");
		this->_server_config.push_back(content.substr(start, end - start + 1));
		this->_nb_server++;
		start = end + 1;
	}
}

size_t Parser::findStartServer (size_t start, std::string &content)
{
	size_t i;

	for (i = start; content[i]; i++) {
		if (content[i] == 's')
			break ;
		if (!isspace(content[i]))
			throw ErrorException("Wrong character out of server scope{}");
	}
	if (!content[i])
		return (start);
	if (content.compare(i, 6, "server") != 0)
		throw ErrorException("Wrong character out of server scope{}");
	i += 6;
	while (content[i] && isspace(content[i]))
		i++;
	if (content[i] == '{')
		return (i);
	else
		throw ErrorException("Wrong character out of server scope{}");
}

size_t Parser::findEndServer (size_t start, std::string &content) {
	size_t i;
	size_t scope;
	
	scope = 0;
	for (i = start + 1; content[i]; i++) {
		if (content[i] == '{')
			scope++;
		if (content[i] == '}') {
			if (!scope)
				return (i);
			scope--;
		}
	}
	return (start);
}
