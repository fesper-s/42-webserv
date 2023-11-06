#include "Parser.hpp"

Parser::Parser() {}

Parser::~Parser() {}

int Parser::checkAndReadFile(const std::string &config_file) {
    std::string content;
    ConfigFile file(config_file);

    if (file.getTypePath(file.getPath()) != 1) {
        std::cout << "file is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (file.checkFile(file.getPath(), 4) == -1) {
        std::cout << "file is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }
    content = file.readFile(config_file);
    if (content.empty()) {
		std::cout << "File is empty" << std::endl;
        exit(EXIT_FAILURE);
    }
    content = removeFileComments(content);
    removeFileWhiteSpace(content);

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
