#include<sstream>
#include<vector>
#include<fstream>
//#include<iostream>
#include<unistd.h>
#include"../bytes/bytes.h"
#include"../utils/utils.h"
namespace hack{
	namespace mem{

enum class permission{
	read=1<<1,
	write=1<<2
};

enum class type_mem{
	heap, undefined
};

struct mem_pars{
	unsigned long beg;
	unsigned long end;
	unsigned int permission;
	type_mem type;
};



auto openmap(void) -> std::fstream;




/**/ void to_proc(std::string proc);

bool permission_exist(unsigned int perm, permission which);



std::vector<mem_pars> parsing_memory(void);
bool change_heap(mem_pars par, std::string what, std::string to);

}

}
