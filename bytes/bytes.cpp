using size_t=unsigned long;
#include"bytes.h"
namespace hack{
const char* strstrb(const char *buf, const char *what, size_t buf_size){
//	for(buf_size;buf_size--){
	for(size_t i =0;i<buf_size;i++){
			if(buf[i]==*(what)){
				const char *tmp=what;
				size_t i1=i;
				while(*tmp && i1<buf_size && *(tmp++)==buf[i1++]);
				if(!*tmp) return &buf[i];
			}
	}
	return nullptr;
}

}

