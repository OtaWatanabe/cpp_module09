#include "PmergeMe.hpp"
#include <iostream>

int	main(int argc, char *argv[]) {
	std::vector<int>	v;
	if (argc <= 1) {
		std::cerr << "pass the possitive integers as command line arguments" << std::endl;
		return 1;
	}
	std::deque<int>	d;
	for (int i = 1; i < argc; ++i) {
		int	n = getInt(std::string(argv[i]));
		v.push_back(n);
		d.push_back(n);
	}
	std::cout << "Befor:\t";
	for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << ' ';
	std::cout << std::endl;
	double	vtime = vectorFordJhonson(v);
	double	dtime = dequeFordJhonson(d);
	std::cout << "After:\t";
	for (size_t i = 0; i < v.size(); ++i) std::cout << v[i] << ' ';
	std::cout << std::endl;
	std::cout << "Time to process a range of " << v.size() << " elements with std::vector: " << vtime << " us" << std::endl;
	std::cout << "Time to process a range of " << d.size() << " elements with std::deque: " << dtime << " us" << std::endl;
}