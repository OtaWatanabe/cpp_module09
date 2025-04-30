#include "BitcoinExchange.hpp"

static void	printError(const std::string& msg) {
	std::cout << "Error: " << msg << std::endl;
}

static bool	trim(std::string& str) {
	size_t	i = 0;

	while (std::isspace(str[i])) ++i;
	if (i == str.size()) return false;
	str.erase(0, i);
	size_t	end = str.size() - 1;
	while (std::isspace(str[end])) --end;
	str.erase(end + 1, str.size() - end);
	return true;
}

static bool	checkDate(const std::string& date) {
	size_t	i = 0;
	int		y = 0;

	if (!isdigit(date[0])) return false;
	while (i < date.size() && date[i] != '-' && i < 4) {
		if (!isdigit(date[i])) return false;
		y = y * 10 + (date[i] - '0');
		++i;
	}
	if (date[i++] != '-') return false;
	int m = (date[i] - '0') * 10 + date[i + 1] - '0';
	if (!isdigit(date[i]) || !isdigit(date[i+1])) return false;
	i += 2;
	if (date[i++] != '-') return false;
	if (!isdigit(date[i]) || !isdigit(date[i+1])) return false;
	int d = (date[i] - '0') * 10 + date[i + 1] - '0';
	if (date[i+2]) return false;
	if (12 < m || m == 0) return false;
	int monthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (monthDays[m-1] < d || d == 0) return false;
	if (m == 2 && (y % 4 || (y % 400 && y % 100 == 0)) && d == 29) return false;
	return true;
}

std::map<std::string, float>	getData(void) {
	std::ifstream	readCSV("data.csv");
	std::map<std::string, float>	ret;

	if (readCSV.fail()) {
		std::cerr << "Failed to open data.csv" << std::endl;
		std::exit(1);
	}

	std::string	strBuf;
	std::getline(readCSV, strBuf);

	while (std::getline(readCSV, strBuf)) {
		std::stringstream	ss(strBuf);

		std::string	date;
		float	val;
		std::getline(ss, date, ',');
		if (ss.fail() || !trim(date) || !checkDate(date)) {
			std::cerr << "data.csv: " << date << " invalid format" << std::endl;
			std::exit(1);
		}
		ss >> val;
		if (ss.fail()) {
			std::cerr << "data.csv: invalid format" << std::endl;
			std::exit(1);
		}
		ret[date] = val;
	}
	readCSV.close();
	return ret;
}

void	calculateInput(const std::map<std::string, float>& bitData, const std::string& filename) {
	std::ifstream	readInput(filename.c_str());

	if (readInput.fail()) {
		std::cerr << "Failed to open input file" << std::endl;
		std::exit(1);
	}

	std::string	strBuf;
	std::getline(readInput, strBuf);
	std::stringstream	ss(strBuf);
	std::string	str1;
	std::string	str2;
	std::getline(ss, str1, '|');
	std::getline(ss, str2);
	if (!trim(str1) || !trim(str2) || str1 != "date" || str2 != "value") {
		printError("bad input => " + strBuf);
	}
	while (std::getline(readInput, strBuf)) {
		std::stringstream	ss(strBuf);
		std::string	date;
		float	money;

		std::getline(ss, date, '|');
		if (ss.fail() || !trim(date) || !checkDate(date)) {
			printError("bad input => " + strBuf);
			continue;
		}
		ss >> money;
		if (ss.fail()) {
			printError("bad input =>" + strBuf);
			continue;
		}
		if (ss.peek() != EOF) ss >> std::ws;
		if (ss.peek() != EOF) {
			printError("bad input =>" + strBuf);
			continue;
		}
		if (money < 0) {
			printError("not a positive number");
			continue;
		}
		if (1000 < money) {
			printError("too large a number");
			continue;
		}
		std::map<std::string, float>::const_iterator	it = bitData.upper_bound(date);
		if (it != bitData.begin()) --it;
		std::cout << date << " => " << money << " = " << it->second * money << std::endl;
	}
	readInput.close();
}
