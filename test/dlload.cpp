#include"../dl/dl.h"
int main(int argc, char**argv){
        auto libs = libraries::dl(argv[1]);
        auto fun = libs.getfunc<void()>(argv[2],argv[1]);
        fun();
}

