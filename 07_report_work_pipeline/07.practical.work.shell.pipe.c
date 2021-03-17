#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define O_RDONLY 00
#define O_WRONLY 01
#define O_RDWR 02
int main()
{
    FILE *f = fopen("file.txt","w");
    int pipefds[2];
    pipe(pipefds);
    pid_t cpid;
    char buf;
    char command[100];
    char parameter[100];

    printf("Type your command:\n");
    scanf("%s",command);
    printf("Type your parameter:\n");
    scanf("%s",parameter);

    cpid = fork();
    if (cpid == -1) {
        perror("fork");
        exit(1);
    }
    if (cpid == 0) {
        int id = creat("./test.txt", 01 | 00 | 02);
        dup2(id, 1);
        //close(pipefds[1]);
        char *args[] = {command, parameter, NULL};
        execvp(command,args);
    } else {
        dup2(pipefds[0], 0);
        close(pipefds[0]);
        close(pipefds[1]);
    }

}
