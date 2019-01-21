#include "submission.h"

//init submission
void submission_init(Submission* submission, int limit_time_s, 
	int limit_memory_mb, int len_ans, char* data_path, 
	char* program_path, char* program_name){

	submission->len_ans = len_ans;
	submission->limit_time_s = limit_time_s;
	submission->limit_memory_mb = limit_memory_mb;
	strcpy(submission->data_path, data_path);
	strcpy(submission->program_path, program_path);
	strcpy(submission->program_name, program_name);

}

