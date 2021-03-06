#ifndef MODEL_GROUP
#define MODEL_GROUP

#include <stdio.h>
#include <string.h>
#include "../utils/filepath.h"

typedef struct Group
{
	int running_time_us, running_memory_kb;
	int limit_time_ms, limit_memory_mb;
	int ans_id;
	char program_name[1001];
	char data_path[1001], program_path[1001];
} Group;



//group init
void group_init(Group* group, int ans_id, int limit_time_s, 
	int limit_memory_mb, char* data_path, char* program_path);

//get input file path
char* group_get_input_filepath(Group* group, char* path_in);

//get output file path
char* group_get_output_filepath(Group* group, char* path_out);

//get answer file path
char* group_get_answer_filepath(Group* group, char* path_ans);

//get error file path
char* group_get_error_filepath(Group* group, char* path_ans);

#endif