#include"inject.h"

#define INITED(ret)         if(!attached[pid]) return ret;
#define SIGTRAP_SINGLESTEP ((5<<12|127<<4)>>4) 
//127==all ok 126==error 0==not have any
//
#define ATTACH_ARR_INITED if(attached==NULL) if(init_attached()==-1)return false;

int init_attached(void){
	int proc_max=open("/proc/sys/kernel/pid_max", O_RDONLY);
	if(proc_max==-1){
		perror("Can't get pid_max");
		return -1;
	}
	char buf[1024];
	if(read(proc_max,buf, sizeof(buf)) == -1){
		perror("Read");
		return -1;
	}
	long long max_pid=atoi(buf);
	attached=calloc(sizeof(bool),max_pid);
	return 0;

}

bool attach_me(void){
	ATTACH_ARR_INITED;
	if(ptrace(PTRACE_TRACEME,0,0,0) == -1)
	{
		perror("Attach");
		return false;
	}
	attached[getpid()]=true;
	return true;
}

bool attach_pid(pid_t pid){
	ATTACH_ARR_INITED;
	if(ptrace(PTRACE_ATTACH, pid,0,0) == -1){
		perror("Attach");
		return false;
	}
	attached[pid]=true;
	return true;
}

bool deattach(pid_t pid){
	INITED(false);

	bool ok = ptrace(PTRACE_DETACH, pid,0,0) != -1;
	if(ok)attached[pid]=false;
	else{
		perror("Deattach: ");
		return false;
	}
	return true;
}

bool freeze(pid_t pid){
	INITED(false);
	return ptrace(PTRACE_SINGLESTEP,pid,0,0) != -1;
}

syscall_hack getcall(pid_t pid){
	syscall_hack err={0,0};
	INITED(err);
	struct user_regs_struct regs;
	regs=getregs(pid);
	if(regs.ax==0 && regs.ip==0) {
		return err;
	}
        syscall_hack ret={regs.ax,regs.ip};
	int status;
	waitpid(pid,&status,0);
	if(status!=SIGTRAP_SINGLESTEP){
		perror("Waitpid");
	}
	return ret;
}

bool putregs(pid_t pid,struct user_regs_struct regs,void *offset){
	INITED(false);
	return ptrace(PTRACE_SETREGS,pid,offset,&regs) == -1;
}

bool putcode(pid_t pid, void * offset, void * data){
	INITED(false);
	return ptrace(PTRACE_PEEKTEXT,pid,&offset,&data) == -1;
}

bool putdata(pid_t pid, void * offset, void * data){
	INITED(false);
	return ptrace(PTRACE_PEEKDATA, pid, &offset, &data) == -1;
}
bool continue_prog(pid_t pid){
	INITED(false);
	return ptrace(PTRACE_CONT,pid,0,0) == -1;
}

struct user_regs_struct getregs(pid_t pid){
struct	user_regs_struct ret;
	INITED(ret);
	if(ptrace(PTRACE_GETREGS,pid,0,&ret) == -1){
		perror("Get regs");
		return ret;
	}
	return ret;
}
