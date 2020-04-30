#include<ctype.h>
#include <math.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

#define LIMIT 100

int commandHandler(int); //client places request with this command

int sockfd; //client socket descriptor

void signalHandler(int sig)
{
	char sendBuffer[LIMIT];
	sprintf(sendBuffer,"----||||----");
	send(sockfd,sendBuffer,LIMIT,0);
	close(sockfd);
	exit(0);
}


int commandHandler(int sockfd)
{
	int tokenCount=0;
	const char delim[2]="$";
	char sendBuffer[LIMIT],recvBuffer[LIMIT], *token;
	printf("\nFormat:<request type><item code><quantity>\n\nExample:\n\n01064 (for 4 units of item 106)\n\tor\n11111 (for close)\nList of Items(item code):\nPen(101)\nPencil(102)\nSharpener(103)\nEraser(104)\nNotebook(105)\nScale(106)\n============================================================\n");


	do
	{
		int tokenCount=0;
		float temp;
		char* lol;
		memset(sendBuffer,0,LIMIT);
		memset(recvBuffer,0,LIMIT);
		gets(sendBuffer);
		send(sockfd,sendBuffer,LIMIT,0);
		recv(sockfd,recvBuffer,LIMIT,0);
		if(recvBuffer[0]-'0'==0)
		{
			token=strtok(recvBuffer,delim);
			tokenCount=0;
			while(token!=NULL)
			{
				tokenCount++;
				token=strtok(NULL,delim);
				if(tokenCount==1) temp=atof(token);
				if(tokenCount==2) lol=token;
			}
			if(tokenCount==2) { printf("Total Amount:%.1f\n",temp ); signalHandler(1);}
			else if(tokenCount==3)
			{
				printf("Price:%.1f ", temp);
				printf("Name:%s\n", lol);
			}
			continue;
		}
		if(recvBuffer[0]-'0'==1)
		{
			token=strtok(recvBuffer,delim);
			token=strtok(NULL,delim);
			printf("%s\n",token);
			continue;
		}
	puts(recvBuffer);
	signalHandler(1);
	}while(1);
}

int main(int argc, char *argv[])
{
	int check;
	int SERVER_PORT = atoi(argv[2]);
	struct sockaddr_in ServAddr;
	//Creating the socket
	sockfd=socket(AF_INET,SOCK_STREAM,0); //socket(internet_family,socket_type,protocol_value) retruns socket descriptor
	if(sockfd<0)
	{
		perror("Cannot create socket!");
		return 0;
	}

	//bzero(&ServAddr,sizeof(ServAddr)); 
	//writes n no. of null nbytes to specified location

	//initializing the server socket
	ServAddr.sin_family=AF_INET;
	ServAddr.sin_addr.s_addr = inet_addr(argv[1]); //using the imput IP
	ServAddr.sin_port = htons(SERVER_PORT); //self defined server port

	if((connect(sockfd,(struct sockaddr *) &ServAddr,sizeof(ServAddr)))<0)
	{
		perror("Server is down!");
		return 0;
	}

	signal(SIGINT,signalHandler);

	printf("\n Connection established :\n ");

	while(1)
	{

		check=commandHandler(sockfd);
		if(check<0)
		{
			printf("Client closing socket!..exiting!\n");
			close(sockfd);
			exit(0);
		}
		else if(check==1)
		{
			close(sockfd);
			exit(0);
		}
	}

	return 0;
}
