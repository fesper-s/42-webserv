#include "webserv.hpp"

int main(int argc, char **argv) {
	if (argc == 1 || argc == 2)
	{
		Parser	parser;
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
