#include "webserv.hpp"

int main(int argc, char **argv) {

	if (argc == 1 || argc == 2) {
		Parser parser;
		std::string conf;

		if (argc == 1)
			conf = "default.conf";
		else
			conf = argv[1];
		parser.checkAndReadFile(conf);
		return 1;
	}
    return 0;
}

//deixei comentado aqui caso queira ver como funciona um servidor http, basta compilar apenas essa main e executar para gerar um
/*
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <fstream>
#include <iostream>
#include <sstream>

#define PORT 8080
#define BUFFER_SIZE 30000

std::string get_file_contents(const std::string& filename) {
    std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
    if (in) {
        std::ostringstream contents;
        contents << in.rdbuf();
        in.close();
        return contents.str();
    }
    return "";
}


int main(int argc, char **argv) {
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Criando socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("In socket");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    memset(address.sin_zero, '\0', sizeof address.sin_zero);

    // Fazendo bind
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("In bind");
        exit(EXIT_FAILURE);
    }

    // Escutando por conexões
    if (listen(server_fd, 10) < 0) {
        perror("In listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("In accept");
            exit(EXIT_FAILURE);
        }

        char buffer[BUFFER_SIZE] = {0};
        if ((valread = read(new_socket, buffer, BUFFER_SIZE)) < 0) {
            printf("There is no bytes to read\n");
        }

        // Parse a solicitação HTTP
        std::string request(buffer);

        // Verifique se a solicitação começa com "GET" e extrai o caminho do arquivo solicitado
        if (request.substr(0, 3) == "GET") {
            size_t start = request.find_first_of(" ");
            size_t end = request.find_first_of(" ", start + 1);
            if (start != std::string::npos && end != std::string::npos) {
                std::string path = request.substr(start + 1, end - start - 1);

                // Se o caminho for "/", defina-o como "index.html" para servir um arquivo padrão
                if (path == "/") {
                    path = "index.html";
                }

                // Construa a resposta HTTP
                std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\n\n";
                std::string file_contents = get_file_contents(path);

                if (!file_contents.empty()) {
                    response += file_contents;
                } else {
                    response = "HTTP/1.1 404 Not Found\n\n";
                }

                // Envie a resposta ao cliente
                write(new_socket, response.c_str(), response.size());
            }
        }

        printf("------------------ Message sent -------------------\n");
        close(new_socket);
    }

    (void)argv;
    (void)argc;
    return 0;
}
*/