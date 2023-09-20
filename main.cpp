#include "webserv.hpp"

int main(int argc, char **argv) {
	if (argc == 1 || argc == 2)
	{
		std::string conf;
		if (argc == 1)
			conf = "default.conf";
		else
			conf = argc[1];
		return 1;
	}
	(void) argv;
	return 0;
}
