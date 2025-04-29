#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[]) {
	if (argc <= 1) {
		std::cerr << "Error: could not open file." << std::endl;
		return 1;
	}
	std::map<std::string, float>	bitData;

	bitData = getData();

	calculateInput(bitData, argv[1]);
}
