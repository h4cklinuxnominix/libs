#include"mem.h"


int main(int argc, char**argv){
	if(argc < 4){
		std::cerr << argv[0] << " $pid $what $to" << std::endl;
		return 1;
	}//end if
	try{
		hack::mem::to_proc(argv[1]);
		//std::cout << "Open map" << std::endl;
		auto lines = hack::mem::parsing_memory();
		for(auto line : lines) {
			if(line.type==hack::mem::type_mem::heap)
				if(hack::mem::change_heap(line,argv[2], argv[3])) return 0;
		}//end for
		return 1;
		//std::cout << "End prog" << std::endl;
	}catch(std::runtime_error & err){//start catch and end try
		std::cerr << err.what() << std::endl;
		return 1;
	}//end catch
}


