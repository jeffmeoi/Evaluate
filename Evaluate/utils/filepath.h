#ifndef UTIL_FILEPATH
#define UTIL_FILEPATH

#include <unistd.h>
#include <string.h>
#include <stdio.h>

//get the absolute path of the program calling the function.
char* filepath_get_absolute_path(char* absolute_path);

//make the path back one level
char* filepath_back(char* path);

//read file content
char* filepath_get_file_content(char* filename, char* content, int maxlen);

//get the length of file
int filepath_file_length(char* filename);

//get the program name from path
char* filepath_get_program_name(char* path, char* name);

#endif
