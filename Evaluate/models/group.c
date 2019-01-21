#include "group.h"


//group init
void group_init(Group* group, int ans_id, int limit_time_s, 
	int limit_memory_mb, char* data_path, char* program_path){
	group->ans_id = ans_id;
	group->limit_time_s = limit_time_s;
	group->limit_memory_mb = limit_memory_mb;
	strcpy(group->data_path, data_path);
	strcpy(group->program_path, program_path);
	filepath_get_program_name(program_path, group->program_name);
}

//get input file path
char* group_get_input_filepath(Group* group, char* path_in){
	sprintf(path_in, "%s%s_%05d.in", 
		group->data_path, group->program_name, group->ans_id);
	return path_in;
}

//get output file path
char* group_get_output_filepath(Group* group, char* path_out){
	sprintf(path_out, "%s%s_%05d.out", 
		group->data_path, group->program_name, group->ans_id);
	return path_out;
}

//get answer file path
char* group_get_answer_filepath(Group* group, char* path_ans){
	sprintf(path_ans, "%s%s_%05d.ans", 
		group->data_path, group->program_name, group->ans_id);
	return path_ans;
}

//get error file path
char* group_get_error_filepath(Group* group, char* path_ans){
	sprintf(path_ans, "%s%s_%05d.err", 
		group->data_path, group->program_name, group->ans_id);
	return path_ans;
}
