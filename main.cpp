#include "webserv.hpp"

int main(int argc, char **argv) {
	if (argc != 2) {
		std::cout << "Try: ./webserv [parameter]" << std::endl;
		return 1;
	}
	(void) argv;
	return 0;
}
