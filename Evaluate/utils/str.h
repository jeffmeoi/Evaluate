#ifndef UTIL_STR
#define UTIL_STR

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

//whether sub in str
int str_in(char * str, char* sub);

/*	!!!make sure that the len of str is enough.*/
//replace "before" in str to "after"
char* str_replace(char* str, char* before, char* after);

//remove the space in the end of str.
char* str_rstrip(char* str);

//removoe the space in the beginning of str.
char* str_lstrip(char* str);

//remove the space in the beginning and the end of str.
char* str_strip(char* str);

//compare str1 with str2.
int str_cmp(char* str1, char* str2);

//compare str1 with str2 in length of n
int str_ncmp(char* str1, char* str2, int n);

//remove all the space in str
char* str_rmspace(char* str);

//copy str to dest.
char* str_cpy(char* dest, char* str);

#endif