#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
int main(){
	struct sockaddr_in saddr;
	struct hostent *h;
	int sockfd;
	unsigned short port = 8080;
	if((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{
		printf("Error creating socket\n");
		exit(1);
	}
	if((h=gethostbyname("localhost")) == NULL) 
		{
			printf("Unknown host\n");
			exit(1);
		}

	memset(&saddr, 0,sizeof(saddr));
	saddr.sin_family = AF_INET;
	memcpy((char *) &saddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	saddr.sin_port = htons(port);
	if(connect(sockfd, (struct sockaddr *) &saddr,sizeof(saddr)) < 0) 
	{
		printf("Cannot connect\n");
		exit(1);
	}
	char s[100];
	//while(1){
	//	if(strcmp(s,"quit")==0){
	//		break;
	//	}
	while(1){
		printf("<Client side> Sharing something:\n");
		scanf("%s",s);
		send(sockfd, s, strlen(s),0);

		char buffer[100];
		memset(buffer,0,sizeof(buffer));
		recv(sockfd, buffer, sizeof(buffer), 0);
		printf("%s\n",(char *)buffer);
	}
	
	
	close(sockfd);
	return 0;
}