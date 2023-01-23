#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include <time.h>
#pragma comment (lib, "ws2_32.lib")
void timer (int);
int main(int argc , char *argv[])
{
	WSADATA wsa ;
	int iResult;
	SOCKET s , new_socket,new_socket1;
	struct sockaddr_in server , client;
	int c, cnt;
	char msg [100];
	char client_reply[2000];
	int recv_size;
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0){
		
		printf("Failed. Error Code : %d",WSAGetLastError());
		return 1;
	}
	printf("Initialised.\n");
	if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}
	printf("Socket created.\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr ("127.0.0.1");
	server.sin_port = htons( 8888 );
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
	}
	puts("Bind done");
	while(1)
	{
		listen(s , 3);
		puts("Waiting for incoming connections...");
		c = sizeof(struct sockaddr_in);
		new_socket = accept(s , (struct sockaddr *)&client, &c);
		if (new_socket == INVALID_SOCKET)
		{
			printf("accept failed with error code : %d" , WSAGetLastError());
		}
		puts("Connection accepted");
		int s=0;
		while(s<3)
		{
			if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
				puts("recv failed");
			else
			{
				client_reply[recv_size] = '\0';
				puts(client_reply);
			}
			timer (1);
			s++;
		}
		iResult = shutdown(new_socket, SD_RECEIVE);
		if (iResult == SOCKET_ERROR) 
		{
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(new_socket);
			WSACleanup();
			return 1;
		}
	}
	return 0;
}
void timer (int sec)
{
	clock_t end;
	end = clock () + sec * CLOCKS_PER_SEC;
	while (clock () <= end);
}