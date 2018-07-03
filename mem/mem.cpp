
#include"mem.h"
#include"../bytes/throws.h"
using namespace hack;
using namespace mem;
namespace hack{
	namespace mem{


 auto openmap(void) -> std::fstream{
	std::fstream map("maps",std::ios::in);
	if(!map.is_open()) throw( std::runtime_error("Can't open maps file") );
	return std::forward<std::fstream>(map);
}



/**/ void to_proc(std::string proc){
	proc="/proc/"+proc;
	if(-1 == chdir(proc.c_str()) ) throws("Can't found ", proc);
}

 bool permission_exist(unsigned int perm, permission which){
			unsigned int whichi=static_cast<unsigned int>(which);
                        return (perm&whichi) == whichi;

}



std::vector<mem_pars> parsing_memory(void){
                auto map=openmap();
		std::vector<mem_pars> vpars;
                constexpr unsigned int streams=1024;
                char line[streams];
  //              std::cout << "Reading" << std::endl;
                while( map.getline(line,sizeof(line)) ){
			auto splited=utils::split(line,'-');
			mem_pars pars;
			std::istringstream(splited[0])>>std::hex>>pars.beg;
			std::istringstream(utils::split(splited[1],' ')[0])>>std::hex>>pars.end;

//			std::cout << pars.beg << " beg" << std::endl;
//			std::cout << pars.end << " end" << std::endl;
			splited=utils::split(splited[1],' ');
//			std::cout << line << std::endl;
			//type=splited[5];
			//perms=splited[1];
			try{
				splited.at(1);
			}catch(std::exception & excp){
//				std::cerr << "Can't parse line, ignored" << std::endl;
				continue;
			}

//			std::cout << splited[1] << std::endl;
			if(splited[1].find("r") != std::string::npos) pars.permission|=static_cast<unsigned int>(permission::read);
			if(splited[1].find("w") != std::string::npos) pars.permission|=static_cast<unsigned int>(permission::write);
//			if( permission_exist(pars.permission, permission::read) )std::cout << "Read permission does exist" << std::endl;
//			if( permission_exist(pars.permission, permission::write) )std::cout << "Write permission does exist" << std::endl;

			splited=utils::split(line,'[');
			try{
			splited.at(1);
//		 	std::cout << splited[1] << std::endl;
		 	if(splited[1].find("heap") != std::string::npos)pars.type=type_mem::heap;
		   	else pars.type=type_mem::undefined; 
			}catch(std::exception & e){}
			vpars.push_back(pars);
                }
		return vpars;

}



 bool change_heap(mem_pars par, std::string what, std::string to){
//	std::fstream mem("mem", std::ios::in|std::ios::binary);
//	mem.seekg(par.beg);
	FILE * mem = fopen("mem","a+");
	if ( mem == nullptr) return false;
	fseek(mem, par.beg, SEEK_SET);
	char buf[par.end-par.beg];
	if ( fread(buf, sizeof(buf),1,mem ) == -1) return false;
//	std::cout << "Buffer: " << buf << std::endl;
	const	char * in=strstrb(buf, what.c_str(),sizeof(buf));
	if(in == nullptr){
//		std::cout << "Not found " <<what << std::endl;
		fclose(mem);
		return false;
	}
	size_t offset=(size_t)(in-(buf));
//	std::cout << "Offset: " << offset << std::endl;
//	mem.seekg(par.beg+offset,std::ios::beg);
	//fseek(mem, offset, SEEK_CUR);
	fseek(mem,offset+par.beg,SEEK_SET);
//	std::cout << "Found on " << ftell(mem) << std::endl;
//	mem << to;
//	mem.write(to.c_str(),to.size());
	fwrite(to.c_str(), to.size(),1,mem);
//	std::cout << "Check!" << std::endl;
	fclose(mem);
	return true;

}//change heap



}
}

