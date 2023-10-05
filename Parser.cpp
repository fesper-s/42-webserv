#include "Parser.hpp"

Parser::Parser()
{}

Parser::~Parser()
{}

int Parser::checkAndReadFile(const std::string &config_file)
{
    std::string content;
    ConfigFile file(config_file);

    if (file.getTypePath(file.getPath()) != 1)
    {
        std::cout << "file is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (file.checkFile(file.getPath(), 4) == -1)
    {
        std::cout << "file is invalid" << std::endl;
        exit(EXIT_FAILURE);
    }
    content = file.readFile(config_file);
    if (content.empty())
    {
		std::cout << "File is empty" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << content << std::endl;
    content = removeFileComments(content);
    content = removeFileWhiteSpace(content);
    std::cout << content << std::endl;

    return (0);
}

std::string Parser::removeFileComments(std::string &content)
{
    std::string result;
    std::istringstream iss(content);
    std::string line;

    while (std::getline(iss, line)) {
        size_t commentPos = line.find('#');
        if (commentPos != std::string::npos) {
            // Remove tudo após o caractere '#', incluindo o próprio caractere
            line.erase(commentPos);
        }
        result += line + "\n"; // Reconstroi a string resultante
    }

    return result;
}


std::string Parser::removeFileWhiteSpace(std::string &content)
{
    std::string result;
    std::istringstream iss(content);
    std::string line;

    while (std::getline(iss, line)) {
        // Verifica se a linha não está em branco (contém caracteres visíveis)
        bool isNonEmpty = false;
        for (size_t i = 0; i < line.length(); i++) {
            if (!std::isspace(line[i])) {
                isNonEmpty = true;
                break;
            }
        }

        if (isNonEmpty) {
            result += line + "\n"; // Mantém linhas não vazias
        }
    }

    return result;
}
