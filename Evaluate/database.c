#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"

int main()
{
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;  
    Config* config = config_init("rabbit", "ans_db", 1, 256);
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, MYSQL_SERVER, MYSQL_USER, MYSQL_PWD, MYSQL_DATABASE, 0, NULL, 0)) 
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    if (mysql_query(conn, "show tables"))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    
    res = mysql_use_result(conn);
    
    printf("MySQL Tables in mysql database:\n");
    
    while ((row = mysql_fetch_row(res)) != NULL)
    {
        printf("%s \n", row[0]);
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    config_del(config);    
    printf("finish! \n");

    return 0;
}

/*#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char* argv[]){
 	pid_t pid;
	if((pid = fork()) < 0){
		printf("Fork error!\n");
		exit(0);
	}else if(pid == 0){
		printf("child\n");
		execl("/bin/ls", "ls", "/home", NULL);
	}else{
		wait(NULL);
		printf("parent\n");
	}

}
*/