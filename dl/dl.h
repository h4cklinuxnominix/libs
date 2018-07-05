#include<dlfcn.h>
#include<map>
#include<iostream>
#include<functional>
//#include<stdarg.h>

namespace libraries{
	class dl{
		protected:
		std::map<std::string,void*> libraries;
		void addlib(void){}
		template<typename ... Args>
		void addlib(std::string lib, Args ... args){
			void*tmp=dlopen(lib.c_str(),RTLD_LAZY);
			if(tmp == nullptr){
				throw(std::runtime_error("Can't open dl from "+lib) );
			}
			libraries[lib]=tmp;
			addlib(args...);
		}
		public:
		template<typename ... Args>
		dl(Args ... args){
			addlib(args...);
		}
		template<typename T>
		auto getfunc(std::string namefunc, std::string lib){
			try{
				libraries.at(lib);
			}catch(std::exception & e){
				throw(std::runtime_error("Can't get library: "+lib) );
			}
			void* fn = dlsym(libraries[lib],namefunc.c_str());
			if(fn==nullptr)
				throw( std::runtime_error("Can't get function "+namefunc+" from "+lib));
			std::function<T> f=reinterpret_cast<T*>(fn);
			return f;
		}
		dl(void);
		dl& operator+(dl & l);
		dl& operator-(dl & l);
		bool operator==(dl & l);
		void* operator[](unsigned long i);
		void* operator[](std::string i);
		dl& operator=(dl & l);
	};
}

