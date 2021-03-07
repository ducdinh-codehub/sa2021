#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdbool.h>
int main(){
	printf("Main before fork()\n");
	char command[100];
	char parameter[100];
	while(true){
		printf("I'm parent\n");
		if(strcmp(command,"break")==0 || strcmp(parameter,"break")==0){
			break;
		}
		printf("Type command:\n");
		scanf("%s",command);
		printf("Type parameter:\n");
		scanf("%s",parameter);
		printf("Your command %s %s\n",command,parameter);
		int pid = fork();
		if(pid == 0){
			printf("I'm child after fork(), launching!");
			char *args[] = {command, parameter, NULL};
			execvp(command,args);
			printf("Finished launching ps -ef\n");
		}
	}
	printf("I'm parent mode");
	return 0;
}
