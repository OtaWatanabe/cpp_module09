#include "PmergeMe.hpp"

size_t	jacob[100];

int	getInt(const std::string& str) {
	int	ret = 0;

	if (str[0] == '-') {
		std::cerr << "The arguments must be positive" << std::endl;
		std::exit(1);
	}
	if (!str[0]) {
		std::cerr << "Empty argument is forbidden" << std::endl;
		std::exit(1);
	}
	for (size_t i = 0; i < str.size(); ++i) {
		if (!std::isdigit(str[i])) {
			std::cerr << "Invalid arguments" << std::endl;
			std::exit(1);
		}
		if (INT_MAX / 10 < ret || (INT_MAX / 10 == ret && INT_MAX % 10 < str[i] - '0')) {
			std::cerr << "Too large an arugument" << std::endl;
			std::exit(1);
		}
		ret = 10 * ret + str[i] - '0';
	}
	return ret;
}

static std::vector<std::pair<int, int> >	binaryInsertion(const std::vector<std::pair<int, int> > &sorted, const std::vector<std::pair<int, int> > &insert) {
	std::vector<std::pair<int, int> >	ret;
	int	stage = 0;
	size_t	finishInsert = 0;
	size_t	sortedI = 0;

	ret.push_back(insert[0]);
	while (1) {
		for (size_t i = 0; i < jacob[stage] && sortedI + i < sorted.size(); ++i) ret.push_back(sorted[sortedI + i]);
		sortedI += jacob[stage];
		size_t	searchSize = ret.size();
		for (size_t j = std::min(insert.size() - 1, finishInsert + jacob[stage]); finishInsert < j; --j) {
			ret.insert(std::lower_bound(ret.begin(), ret.begin() + searchSize, insert[j]), insert[j]);
		}
		finishInsert += jacob[stage];
		if (insert.size() - 1 <= finishInsert) {
			for (size_t i = sortedI; i < sorted.size(); ++i) ret.push_back(sorted[i]);
			return ret;
		}
		++stage;
	}
}

static std::vector<std::pair<int, int> >	vectorFordJhonson(const std::vector<std::pair<int, int> > &v) {
	std::vector<std::pair<int, int> > larger;

	if (v.size() <= 1) return v;
	std::pair<int, int>	last = v[v.size()-1];

	for (size_t i = 0; i + 1 < v.size(); i += 2) {
		if (v[i] < v[i + 1]) larger.push_back(std::make_pair(v[i + 1].first, i));
		else larger.push_back(std::make_pair(v[i].first, i + 1));
	}

	larger = vectorFordJhonson(larger);
	std::vector<std::pair<int, int> >	smaller;

	for (size_t i = 0; i < larger.size(); ++i) {
		int	second = larger[i].second;
		smaller.push_back(v[second]);
		if (second % 2) larger[i].second = v[second - 1].second;
		else larger[i].second = v[second + 1].second;
	}
	if (v.size() % 2) smaller.push_back(last);

	return binaryInsertion(larger, smaller);
}

double	vectorFordJhonson(std::vector<int> &v) {
	std::vector<std::pair<int, int> > vpair(v.size());
	double	start = std::clock();

	jacob[0] = 2;
	jacob[1] = 2;
	for (int i = 1; jacob[i] < v.size(); ++i) {
		jacob[i + 1] = jacob[i] + 2 * jacob[i - 1];
	}

	for (size_t i = 0; i < v.size(); ++i) vpair[i] = std::make_pair(v[i], 0);
	std::vector<std::pair<int, int> >	psorted = vectorFordJhonson(vpair);

	for (size_t i = 0; i < v.size(); ++i) v[i] = psorted[i].first;

	return static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1e6;
}

static std::deque<std::pair<int, int> >	binaryInsertion(const std::deque<std::pair<int, int> > &sorted, const std::deque<std::pair<int, int> > &insert) {
	std::deque<std::pair<int, int> >	ret;
	int	stage = 0;
	size_t	finishInsert = 0;
	size_t	sortedI = 0;

	ret.push_back(insert[0]);
	while (1) {
		for (size_t i = 0; i < jacob[stage] && sortedI + i < sorted.size(); ++i) ret.push_back(sorted[sortedI + i]);
		sortedI += jacob[stage];
		size_t	searchSize = ret.size();
		for (size_t j = std::min(insert.size() - 1, finishInsert + jacob[stage]); finishInsert < j; --j) {
			ret.insert(std::lower_bound(ret.begin(), ret.begin() + searchSize, insert[j]), insert[j]);
		}
		finishInsert += jacob[stage];
		if (insert.size() - 1 <= finishInsert) {
			for (size_t i = sortedI; i < sorted.size(); ++i) ret.push_back(sorted[i]);
			return ret;
		}
		++stage;
	}
}

static std::deque<std::pair<int, int> >	dequeFordJhonson(const std::deque<std::pair<int, int> > &d) {
	std::deque<std::pair<int, int> > larger;

	if (d.size() <= 1) return d;
	std::pair<int, int>	last = d[d.size()-1];

	for (size_t i = 0; i + 1 < d.size(); i += 2) {
		if (d[i] < d[i + 1]) larger.push_back(std::make_pair(d[i + 1].first, i));
		else larger.push_back(std::make_pair(d[i].first, i + 1));
	}

	larger = dequeFordJhonson(larger);
	std::deque<std::pair<int, int> >	smaller;

	for (size_t i = 0; i < larger.size(); ++i) {
		int	second = larger[i].second;
		smaller.push_back(d[second]);
		if (second % 2) larger[i].second = d[second - 1].second;
		else larger[i].second = d[second + 1].second;
	}
	if (d.size() % 2) smaller.push_back(last);

	return binaryInsertion(larger, smaller);
}

double	dequeFordJhonson(std::deque<int> &d) {
	std::deque<std::pair<int, int> > dpair(d.size());
	double	start = std::clock();

	jacob[0] = 2;
	jacob[1] = 2;
	for (int i = 1; jacob[i] < d.size(); ++i) {
		jacob[i + 1] = jacob[i] + 2 * jacob[i - 1];
	}

	for (size_t i = 0; i < d.size(); ++i) dpair[i] = std::make_pair(d[i], 0);
	std::deque<std::pair<int, int> >	psorted = dequeFordJhonson(dpair);

	std::deque<int>	ret;
	for (size_t i = 0; i < d.size(); ++i) d[i] = psorted[i].first;

	return static_cast<double>(std::clock() - start) / CLOCKS_PER_SEC * 1e6;
}
