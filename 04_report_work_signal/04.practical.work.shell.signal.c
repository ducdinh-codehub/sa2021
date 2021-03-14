#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<signal.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
int childpid = 0;
void handler(int);
int main(void){
	printf("Main before fork\n");
	char command[100];
	char parameter[100];
    signal(SIGTSTP, handler); // Register signal
    signal(SIGTERM, handler);
    signal(SIGINT, handler);
	while(true){
		printf("I'm parent\n");
		printf("Signal handler example\n");
		printf("*NOTE: type '-quit' to close shell !\n");
		printf("Type command:\n");
		scanf("%s",command);
		printf("Type parameter:\n");
		scanf("%s",parameter);
		printf("Your command %s %s\n",command,parameter);
        if(strcmp(command,"-quit")==0 || strcmp(parameter,"-quit")==0){
            break;
        }
		int pid = fork();
		printf("Process id: %d\n",pid);
		if(pid){
            printf("I'm parent wait and I'm waiting my child\n");
		    childpid = pid;
		    waitpid(pid, NULL, 0);
		}else{
		    printf("I'm a child\n");
            char *args[] = {command, parameter, NULL};
            execvp(command,args);
		}
	}
	return 0;
}
void handler(int signal_num){
    printf("Signal %d => ", signal_num);
    switch(signal_num){
        case SIGTSTP:
            printf("Pause\n");
            kill(childpid, SIGTSTP);
            break;
        case SIGINT:
        case SIGTERM:
            printf("Terminated\n");
            kill(childpid, SIGTERM);
            exit(0);
            break;
    }
}