#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <netinet/in.h>
int main(){
	int sockfd, clen, clientfd; 
	struct sockaddr_in saddr, caddr;
	unsigned short port = 8080;
	if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error creating socket\n");
		exit(1);
	}

	memset(&saddr, 0,sizeof(saddr));
	saddr.sin_family = AF_INET; // tcp or udp
	saddr.sin_addr.s_addr = htonl(INADDR_ANY);
	saddr.sin_port = htons(port); // server port

	if((bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)) 
		{
			printf("Error binding\n");
			exit(1);
		}

	if(listen(sockfd, 5) < 0) 
		{
			printf("Error listening\n");
			exit(1);
		}
	
		clen=sizeof(caddr);
	if((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) 
		{	
			printf("Error accepting connection\n");
			exit(1);
		}
	while(1){
			char buffer[100];
			memset(buffer,0,sizeof(buffer));
			recv(clientfd, buffer, sizeof(buffer), 0);
			printf("%s\n",(char *)buffer);
			char alertNoti[100] = "<Server side> Msg reaches server";
			send(clientfd, alertNoti, strlen(alertNoti),0);
		}
	return 0;
}
