#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP
# include <iostream>
# include <string>
# include <fstream>
# include <sstream>
# include <map>
# include <cstdlib>

std::map<std::string, float>	getData(void);
void	calculateInput(const std::map<std::string, float>& bitData, const std::string& filename);

#endif
