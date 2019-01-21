#ifndef MODEL_SUBMISSION
#define MODEL_SUBMISSION
#include <stdio.h>
#include <string.h>
#include "../models/group.h"
#include "../utils/filepath.h"

typedef struct Submission
{
	int len_ans;
	int limit_time_s, limit_memory_mb;
	char program_path[101], data_path[101];
	char program_name[101];
} Submission;

//init submission
void submission_init(Submission* submission, int limit_time_s, 
	int limit_memory_mb, int len_ans, char* data_path, 
	char* program_path, char* program_name);


#endif
