#ifndef MODEL_PROCESS
#define MODEL_PROCESS

#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>


typedef struct Process
{
	pid_t pid;
	struct rusage rusage;		//resource infomation
	int status;					//exit status
	int time_us, memory_kb;		//running time and max rss memory

} Process;

//get pid by popen a subprocess to execute the cmd of "pidof program name"
int process_get_pid(Process* process, char* name);

//get running information from the rusage of process
void process_get_running_information(Process* process);

#endif