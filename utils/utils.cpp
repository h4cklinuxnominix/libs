#include"utils.h"

using namespace utils; 
namespace utils{

std::vector<std::string> split(std::string where, char delim){
        std::string line;
        std::istringstream strm(where);
        std::vector<std::string> returns;
        while( std::getline(strm, line, delim) ){
                returns.push_back(line);
        }
        return returns;
}
template<typename T, typename std::size_t size>
auto get_arr_size(T (&arr)[size]){
        return size;
}
}

