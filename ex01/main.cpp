#include "RPN.hpp"

int	main(int argc, char *argv[]) {
	if (argc == 1) {
		std::cerr << "pass a Polish mathmatical expression" << std::endl;
		return 1;
	}
	processPolish(argv[1]);
}