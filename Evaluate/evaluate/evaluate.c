#ifndef EVALUATE
#define EVALUATE

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../utils/str.h"
#include "../utils/results.h"
#include "../utils/filepath.h"
#include "../models/submission.h"
#include "../models/process.h"


typedef struct Evaluate{
	
	Submission submission;
	Process process;
	int result;
	int total_memory_mb, total_time_us;
	int average_memory_mb, average_time_us;
	char out[1001];
	char project_path[1001];
	char path_out[1001];
	char path_run[1001];

} Evaluate;

#endif

Evaluate evaluate;

void evaluate_init(Evaluate* evaluate, int limit_time_s, 
	int limit_memory_mb, int len_ans, char* data_path, 
	char* program_path, char* program_name){

	int result = 0;
	int total_memory_mb = 0, total_time_us = 0;
	int average_memory_mb = 0, average_time_us = 0;

	filepath_back(filepath_get_absolute_path(evaluate->project_path));

	submission_init(&evaluate->submission, limit_time_s, 
		limit_memory_mb, len_ans, data_path, program_path, 
		program_name);

}


int main(int argc, char* argv[]){

	int i = 0;

	char str_ans_id[10];

	evaluate_init(&evaluate, 
		atoi(argv[1])/*limit time*/, 
		atoi(argv[2])/*limit memory*/, 
		atoi(argv[3])/*len of ans*/, 
		argv[4]/*data path*/, 
		argv[5]/*program path*/,
		argv[6]/*program name*/);

	sprintf(evaluate.path_run, "%srun/run", evaluate.project_path);
	sprintf(evaluate.path_out, "%srun/run.out", evaluate.project_path);

	int ans_index;
	for(ans_index = 1; ans_index <= evaluate.submission.len_ans; ans_index++){
		
		sprintf(str_ans_id, "%d", ans_index);
		
		//fork a subprocess to execute "run"
		pid_t pid = fork();				
		if(0 == pid){
			//run the program "run"
			execl(evaluate.path_run, "run", 
				str_ans_id, 
				argv[1]/*str limit time*/, 
				argv[2]/*str limit memory*/, 
				evaluate.submission.data_path, 
				evaluate.submission.program_path, 
				evaluate.submission.program_name, 
				NULL);
		}else{
			int status;
			waitpid(pid, &status, 0);	//wait subprocess exit.

			//get result from file
			FILE* fp = fopen(evaluate.path_out, "r");
			int memory_mb, time_us;
			fscanf(fp, "%d %dus %dkb", &evaluate.result, &time_us, &memory_mb);
			fclose(fp);

			//add time to totoal time
			//add memory to total memory
			evaluate.total_time_us += time_us;
			evaluate.total_memory_mb += memory_mb;

			//calculate average time and average memory
			evaluate.average_time_us = evaluate.total_time_us / ans_index;
			evaluate.average_memory_mb = evaluate.total_memory_mb / ans_index;

			//if subprocess exit is unnormal
			if(!WIFEXITED(status))
				evaluate.result = SE;

			//if result is not AC
			if(evaluate.result != AC)
				break;
		}
	}
	//printf result
	printf("%s %dus %dkb %d", str_result[evaluate.result], evaluate.average_time_us, 
		evaluate.average_memory_mb, --ans_index);	
}
