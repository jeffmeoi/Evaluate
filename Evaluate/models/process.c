#include "process.h"

//get pid by popen a subprocess to execute the cmd of "pidof program name"
pid_t process_get_pid(Process* process, char* name){
	if(process == NULL){
		char cmd_pidof[20];
		int pid = 0;
		sprintf(cmd_pidof, "pidof %s", name);
		FILE* p_get_pid = popen(cmd_pidof, "r");
		fscanf(p_get_pid, "%d", &pid);
		pclose(p_get_pid);
		return pid;
	}else{
		return process->pid;
	}
}

//get running information from the rusage of process
void process_get_running_information(Process* process){
	process->memory_kb = process->rusage.ru_maxrss;
	process->time_us = (process->rusage.ru_utime.tv_sec + 
		process->rusage.ru_stime.tv_sec) * 1000000 + 
		(process->rusage.ru_utime.tv_usec + 
		process->rusage.ru_stime.tv_usec);

}