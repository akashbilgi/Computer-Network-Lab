#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<iostream>
#include<string>
#include <time.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;

void timer (int sec)
{
	clock_t end;

	end = clock () + sec * CLOCKS_PER_SEC;
	while (clock () <= end);
}

int main(int argc , char *argv[])
{

	WSADATA wsa ;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c, cnt;
	char msg [100];
	char client_reply[2000];
	int recv_size;
	string ms[6];
	int m;
	int ack;
	char check[10];
	int wait=0;
	int flag[100];
	int z=0;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d\n" , WSAGetLastError());
	}
	printf("Socket created.\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr ("127.0.0.1");
	server.sin_port = htons( 8888 );

	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d\n" , WSAGetLastError());
	}
	puts("Bind done");
	listen(s , 3);

	puts("Waiting for incoming connections...\n");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

	puts("Connection accepted\n");

	while(1)
	{

start: if((recv_size = recv(new_socket , msg , 2000 , 0)) == SOCKET_ERROR)
	   {
		   puts("Waiting\n");
		   timer(2);
		   goto start;
	   }		
	else 
	{
		msg[recv_size] = '\0';
		if(msg[0] == '1')
		{
			printf("Press 1 to recieve the messages from client. otherwise press 0:\n");
			gets(check);
			
			send(new_socket , check , strlen(check) , 0);
			if(strcmp(check,"0")==0)
			{
				goto start;
			}

		}
		else
		{
			goto start;
		}
	}

	window: if((recv_size = recv(new_socket , msg , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("Waiting\n");
		timer(2);
		goto window;

	}
	else 
	{ 
		msg[recv_size] = '\0';
		if(msg[0] == '5'){m=5;}
		else if(msg[0] == '4'){m=4;}
		else if(msg[0] == '3'){m=3;}
		else if(msg[0] == '2'){m=2;}
		else {m=1;}
		printf("Windows size is :%d\n",m);
		//puts(msg);
	}

	while(1)
	{
		printf("**************************************\n");
		for(int d=0;d<m;d++)
		{
			flag[d] = 0;
		}
		for(int d=0;d<m;d++)
		{
			
			cc:if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
			{
				timer(2);
				if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
				{
					puts("Recv failed\n");
					strcpy(msg,"Message not received\n");
					wait++;
					if(wait>=m)
					{
						goto bb;
					}
					send(new_socket , msg , strlen(msg) , 0);
				}
			}

			else
			{
				client_reply[recv_size] = '\0';
				printf("Frame recieved is:");
				puts(client_reply);
				if(strcmp(client_reply,"done")==0)
				{
					goto aa;
				}
				strcpy(msg,"Message received\n");
				send(new_socket , msg , strlen(msg) , 0);
				//goto cc;
			}
		}
	}
aa: printf("Message is recieved completely\n");
	}
bb:	system("pause");
	return 0;
}