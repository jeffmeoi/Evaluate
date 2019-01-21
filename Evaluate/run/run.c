#ifndef RUN
#define RUN

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>
#include "../utils/str.h"
#include "../utils/filepath.h"
#include "../utils/results.h"
#include "../models/process.h"
#include "../models/group.h"


typedef struct Run{
	Group group;
	Process process;

	char run_out[1001], run_err[1001];
	char ans[100001], output[100001], err[100001];	//output limit length 100000
	int result, output_maxlen;
	char ps_cmd[1001];
	char data_path[1001], program_path[1001];
	struct timeval tv_begin, tv_end;		//get system time
	//clock_t begin, end;

} Run;

#endif


Run run;


int ans_cmp(){

	char temp_str[1001];

	//get running time and memory used
	run.process.memory_kb = run.process.rusage.ru_maxrss;

	//get delta time(us)
	gettimeofday(&run.tv_end, NULL);
	run.process.time_us = 1000000 * ( run.tv_end.tv_sec - run.tv_begin.tv_sec )
	 + run.tv_end.tv_usec - run.tv_begin.tv_usec;


	//get output and answer from file
	filepath_get_file_content(group_get_output_filepath(
		&run.group, temp_str), run.output, run.output_maxlen);
	filepath_get_file_content(group_get_answer_filepath(
		&run.group, temp_str), run.ans, run.output_maxlen);
	filepath_get_file_content(run.run_err, run.err, run.output_maxlen);

	//'\r\n' in windows and '\n' in linux. remove space in the end.
	str_rstrip(str_replace(run.output, "\r", ""));
	str_rstrip(str_replace(run.ans, "\r", ""));

	//those are used to judge whether is PE
	char output_without_space[100001], ans_without_space[100001];
 	str_rmspace(str_cpy(output_without_space, run.output));
 	str_rmspace(str_cpy(ans_without_space, run.ans));

 	if(run.process.time_us <= 0 || run.process.memory_kb <= 0){
 		return SE;
 	}else if(run.process.time_us > run.group.limit_time_s*1000000){
		return TLE;
	}else if(run.process.memory_kb > run.group.limit_memory_mb * 1024){
		return MLE;
	}else if(strlen(run.err) != 0){
		return RE;
	}else if(filepath_file_length(group_get_output_filepath(&run.group, temp_str)) > run.output_maxlen){
		return OLE;	//if the length of output out of max len, OLE
 	}else if(0 == str_cmp(run.output, run.ans)){
		return AC;
	}else if(0 == str_cmp(output_without_space, ans_without_space)){
		return PE;
	}else{
		return WA;
	}
	return SE;
}


/*init run*/
void run_init(Run* run, int ans_id, int limit_time_s, int limit_memory_mb, 
	char* data_path, char* program_path){

	char temp_str[1001];
	run->output_maxlen = 100001;
	str_cpy(run->data_path, data_path);
	str_cpy(run->program_path, program_path);
	group_init(&run->group, ans_id, limit_time_s, limit_memory_mb, 
		data_path, program_path);
	sprintf(run->run_out, "%srun.out", 
		filepath_get_absolute_path(temp_str));
	sprintf(run->run_err, "%sevaluate/evaluate.err", 
		filepath_back(filepath_get_absolute_path(temp_str)));
	fclose(fopen(run->run_out, "w"));
	fclose(fopen(run->run_err, "w"));
	sprintf(run->ps_cmd, "ps aux | grep %s", program_path);


}

int exec_program_by_type(char* type, char* program_path){

	char temp_str[1001];
	if(0 == str_cmp(type, "c") || 0 == str_cmp(type, "cpp"))
		return execl(program_path, filepath_get_program_name(program_path, temp_str), NULL);
	else if(0 == str_cmp(type, "python3"))
		return execl("/usr/bin/python3", "python3", program_path, NULL);
	else if(0 == str_cmp(type, "python"))
		return execl("/usr/bin/python", "python", program_path, NULL);
	else if(0 == str_cmp(type, "java"))
		return execl("/usr/bin/java", "java", program_path, NULL);
}

void limit(){
	
	struct rlimit r;
	r.rlim_cur = run.group.limit_time_s;
	r.rlim_max = run.group.limit_time_s + 1;
	setrlimit(RLIMIT_CPU, &r);

	r.rlim_cur = run.group.limit_memory_mb * 1024 * 1024;
	r.rlim_max = (run.group.limit_memory_mb + 4) * 1024 * 1024;
	setrlimit(RLIMIT_AS, &r);
	setrlimit(RLIMIT_RSS, &r);

	r.rlim_cur = 0, r.rlim_max = 0;
	setrlimit(RLIMIT_NPROC, &r);

}

void write_result(int result, int time, int memory){

	FILE* fp = fopen(run.run_out, "w");
	fprintf(fp, "%d %dus %dkb", result, time, memory);
	fclose(fp);
}

int main(int argc, char* argv[]){

	char temp_str[1001];
	
	run_init(&run, 
		atoi(argv[1])/*ans id*/, 
		atoi(argv[2])/*limit time*/, 
		atoi(argv[3])/*limit memory*/, 
		argv[4]/*data path*/, 
		argv[5]/*program path*/);

	//if access successfully, return 0, otherwise return -1.
	if(access(group_get_input_filepath(&run.group, temp_str), F_OK)
		|| access(run.program_path, F_OK)){

		FILE* fp = fopen(run.run_out, "w");
		fprintf(fp, "%d %dus %dkb", SE, 0, 0);
		fclose(fp);
	}

	group_get_input_filepath(&run.group, temp_str);
	int fd_in = open(temp_str, O_RDONLY | O_CREAT, 0777);	//fd of input file

	group_get_output_filepath(&run.group, temp_str);
	int fd_out = open(temp_str, O_WRONLY | O_CREAT, 0777);	//fd of output file


	int fd_err = open(run.run_err, O_WRONLY | O_CREAT, 0777);	//fd of output file

	gettimeofday(&run.tv_begin, NULL);		//begin time

	//clock is similar with CPU time, gettimeofday get system time
	pid_t sub_pid = fork();		//new a subprocess to run test program

	if(0 == sub_pid){			//subprocess
		
		//close original input and output file
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
		//redirect input and output file
		dup2(fd_in, STDIN_FILENO);
		dup2(fd_out, STDOUT_FILENO);
		dup2(fd_err, STDERR_FILENO);

		limit();

		//start test program
		exec_program_by_type(argv[6], run.group.program_path);
	}else{			//father process

		//wait4 for rusage to get running information
		if(-1 != wait4(sub_pid, &run.process.status, 0, &run.process.rusage)){
			run.result = ans_cmp();
		}else{
			run.result = SE;
		}
		//close file to avoid something wrong.
		close(fd_in);
		close(fd_out);
		close(fd_err);
		
		//compare answer and output to get result and output result
		write_result(run.result, run.process.time_us, run.process.memory_kb);
	}
}
