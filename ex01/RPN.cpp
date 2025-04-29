#include "RPN.hpp"

static void	calculate(std::stack<int>& st, char op) {
	if (st.size() < 2) {
		std::cerr << "invalid expression: cannot calculate" << std::endl;
		std::exit(1);
	}
	int	x = st.top();
	st.pop();
	int	y = st.top();
	if (op == '-') st.top() = y - x;
	else if (op == '+') st.top() = x + y;
	else if (op == '*') st.top() = x * y;
	else if (op == '/') {
		if (x == 0) {
			std::cerr << "error: divide by 0" << std::endl;
			std::exit(1);
		}
		st.top() = y / x;
	}
	else {
		std::cerr << "invalid expression: '" << op << '\'' << std::endl;
		std::exit(1);
	}
}

void	processPolish(const std::string& expression) {
	std::stack<int>	st;
	size_t	i = 0;

	while (expression[i]) {
		if (std::isdigit(expression[i])) st.push(expression[i] - '0');
		else if (!std::isspace(expression[i])) calculate(st, expression[i]);
		++i;
	}
	if (st.size() != 1) {
		std::cerr << "the numbers of integers and operators don't match" << std::endl;
		std::exit(1);
	}
	std::cout << st.top() << std::endl;
}
