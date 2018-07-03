
#include<string>
#include<vector>
#include<sstream>

namespace utils{

std::vector<std::string> split(std::string where, char delim=' ');

template<typename T, typename std::size_t size> auto get_arr_size(T (&arr)[size]);

}
