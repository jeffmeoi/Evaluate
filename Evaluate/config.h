#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MYSQL_SERVER "localhost"
#define MYSQL_USER "www"
#define MYSQL_PWD "Xie20000713!"
#define MYSQL_DATABASE "testDB"
#define MYSQL_ANS_DB "ans_db"
#define MYSQL_IN_DB "in_db"

typedef struct Config
{
	char name[55];
	int limit_time;
	int limit_memory;
} Config;

/*init config.*/
Config* config_init(char* name, char* ans_db_table, int limit_time, int limit_memory){

	Config* config = (Config*)malloc(sizeof(Config));
	sscanf(name, "%s", config->name);
	config->limit_time = limit_time;
	config->limit_memory = limit_memory;

	return config;
}

/*free config.*/
int config_del(Config* config){
	free(config);
	return 0;

}
