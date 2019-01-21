#include "filepath.h"

//get the absolute path of the program calling the function.
char* filepath_get_absolute_path(char* absolute_path){

	int cnt = readlink("/proc/self/exe", absolute_path, 100);
	for (int i = cnt; i >=0; --i){
	    if (absolute_path[i] == '/'){
	        absolute_path[i+1] = '\0';
	        break;
	    }
	}
	return absolute_path;
}

//make the path back one level
char* filepath_back(char* path){
	int len = strlen(path);
	for (int i = len-2; i >=0; --i){
	    if (path[i] == '/'){
	        path[i+1] = '\0';
	        break;
	    }
	}
	return path;
}

//read file content
char* filepath_get_file_content(char* filename, char* content, 
	int maxlen){
	
	FILE* fp = fopen(filename, "r");
	int i, c;
	for(i = 0; i < maxlen && (c = fgetc(fp)) != EOF; i++)
		content[i] = c;
	content[i] = '\0';
	fclose(fp);

	return content;
}

//get the length of file
int filepath_file_length(char* filename){
	FILE* fp = fopen(filename, "r");
	fseek(fp, 0, SEEK_END);
    int len = ftell(fp);
    fclose(fp);
    return len;
}