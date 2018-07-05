#include<linux/user.h>
#include<sys/ptrace.h>
#include<unistd.h>
#include<stdbool.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

#ifdef __cplusplus
extern "C"{// not c++filt shit
#endif
	typedef struct syscall_hack{
		long long call; //eax
		long long ip; // instruction index
	}syscall_hack;

	#define eprintf(...) fprintf(stderr, __VA_LIST__)
	static bool * attached;
//	static pid_t attached_pid;
	int init_attached(void);

	bool attach_me(void);
	bool attach_pid(pid_t);

	bool freeze(pid_t); // freeze
	bool (*start_singlestep)(void)=(void*)&freeze;
	syscall_hack getcall(pid_t );
	bool (*unfreeze)(void) = (void*)&getcall;


	bool putregs(pid_t,struct user_regs_struct,void *offset);
	bool putcode(pid_t,void * offset, void * data); // put in .text
	bool putdata(pid_t,void * offset, void * data); // put in .data

	bool inject_lib(pid_t,char pathlib[], char funcname[]);


#ifdef __cplusplus
}
#endif
