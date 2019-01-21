#include "str.h"

//whether sub in str
int str_in(char * str, char* sub){
	int len_str = strlen(str);
	int len_sub = strlen(sub);
	
	if(len_sub > len_str)		return 0;
	
	for(int i = 0; i < len_str - len_sub + 1; i++){
		if(0 == strncmp(str+i, sub,len_sub))
			return 1;
	}
	return 0;
}

/*	!!!make sure that the len of str is enough.*/
//replace "before" in str to "after"
char* str_replace(char* str, char* before, char* after){


	int len_str = strlen(str);
	int len_before = strlen(before);
	int len_after = strlen(after);
	
	if(len_str == 0)	return str;

	if(len_before > len_str)		return str;

	char* re_str = (char*)malloc(sizeof(char) * len_str);
	int i = 0, cur = 0;
	while(i < len_str - len_before + 1){
		if(0 == strncmp(str + i, before, len_before)){
			i += len_before;
			for(int j = 0; j < len_after; j++)
				re_str[cur++] = after[j];
		}else{
			re_str[cur++] = str[i++];
		}
	}
	for(int i = 0; i < cur; i++)
		str[i] = re_str[i];
	str[cur] = '\0';

	free(re_str);

	return str;
}

//remove the space in the end of str.
char* str_rstrip(char* str){

	int index = strlen(str) - 1;
	while(index >= 0 && isspace(str[index]))		
		str[index--] = '\0';
	return str;
}

//removoe the space in the beginning of str.
char* str_lstrip(char* str){
	int index = 0;
	int len_str = strlen(str);
	while(isspace(str[index]))		
		index++;
	for(int i = 0; i < len_str - index; i++)
		str[i] = str[i + index];
	str[len_str - index] = '\0';
	return str;
}

//remove the space in the beginning and the end of str.
char* str_strip(char* str){
	return str_lstrip(str_rstrip(str));
}

//compare str1 with str2.
int str_cmp(char* str1, char* str2){
	return strcmp(str1, str2);
}

//compare str1 with str2 in length of n
int str_ncmp(char* str1, char* str2, int n){
	return strncmp(str1, str2, n);
}

//remove all the space in str
char* str_rmspace(char* str){
	return str_replace(str_replace(str_replace(str, "\t", ""), 
	 	"\n", ""), " ", "");
}

//copy str to dest.
char* str_cpy(char* dest, char* str){
	return strcpy(dest, str);
}