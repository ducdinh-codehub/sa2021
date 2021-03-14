#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
#include<signal.h>
#include<stdlib.h>
void handler(int signal_num){
    printf("Signal %d => ", signal_num);
    switch(signal_num){
        case SIGTSTP:
            printf("Pause\n");
            break;
        case SIGINT:
        case SIGTERM:
            printf("Terminated\n");
            exit(0);
            break;
    }
}
int main(void){
    /*
    // Basic example.
    // ctrl z
    signal(SIGTSTP,handler);
    // ctrl c or killed
    signal(SIGINT,handler);
    signal(SIGTERM,handler);
    while(1) {
        sleep(1);
        printf(".\n");
    }*/
	printf("Main before fork\n");
	char command[100];
	char parameter[100];
	while(true){
		printf("I'm parent\n");
		printf("Signal handler example\n");
		if(strcmp(command,"break")==0 || strcmp(parameter,"break")==0){
			break;
		}
		printf("Type command:\n");
		scanf("%s",command);
		printf("Type parameter:\n");
		scanf("%s",parameter);
		printf("Your command %s %s\n",command,parameter);
		int pid = fork();
		printf("Process id: %d",pid);
		if(pid == 0){
			printf("I'm child after fork(), launching!");
			char *args[] = {command, parameter, NULL};
			execvp(command,args);
            kill(pid, SIGKILL);
            printf("Finished launching ps -ef\n");
		}
        signal(SIGTSTP, handler);
        signal(SIGTERM, handler);
        printf("Finished launching ps -ef\n");
	}
	printf("I'm parent mode");
	return 0;
}
