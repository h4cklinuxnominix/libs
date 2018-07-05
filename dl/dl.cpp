//#include<dlfcn.h>
//#include<map>
//#include<iostream>
//#include<functional>
//#include<stdarg.h>
//#include<sys/ptrace.h>
//#include<linux/user.h>
#include"dl.h"
#ifdef WITHOUT_DL 
	#error "Can't for a while compile that without dl library"
#endif
namespace libraries{
		std::map<std::string,void*> libraries;
		dl& dl::operator+(dl & l){
			for(auto lib : l.libraries)
				libraries[lib.first]=(lib.second);
		}

		dl& dl::operator-(dl & l){
			for(auto lib : l.libraries)
				for(auto lib1 : libraries)
					if(lib.second==lib1.second)libraries.erase(lib.first);
		}

		bool dl::operator==(dl & l){
			for(auto lib : l.libraries){
				try{
					libraries.at(lib.first);
				}catch(std::exception & e){return false;}
			}
		}

		void* dl::operator[](unsigned long i){
			for(auto lib : libraries){
				if(i == 0) return lib.second;
				else i--;
			}
		}
		void* dl::operator[](std::string i){
			return libraries[i];
		}

		dl& dl::operator=(dl & l){
			libraries=l.libraries;
		}
}

