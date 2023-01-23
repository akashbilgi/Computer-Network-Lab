#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
int main(int argc , char *argv[])
{
	WSADATA wsa ;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c, cnt;
	int i=0, j=0, count=0;

	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
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
	listen(s , 3);

	puts("Waiting for incoming connections...");

	c = sizeof(struct sockaddr_in);
	new_socket = accept(s , (struct sockaddr *)&client, &c);
	if (new_socket == INVALID_SOCKET)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

	puts("Connection accepted");
	while(1)
	{
		char msg [100];
		char client_reply[2000];
		int recv_size;
		i=0; j=0; count=0;
		if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
			puts("recv failed");
		else 
		{ 
			client_reply[recv_size] = '\0';
			printf("Message received from client: ");
			puts(client_reply);
			char original_msg[1000];

			//De-Stuffing

			for(i=8;i<strlen(client_reply)-8;i++)
			{
                if(count == 5)
                {
                        count = 0;
                        continue;
                }
                if(client_reply[i] == '1')
                        count++;
                else
                        count=0;

                original_msg[j++] = client_reply[i];
        }
        original_msg[j] = '\0';
        printf("\nAfter De-Stuffing : ");
        puts(original_msg);

			printf ("Server: ");
			gets (msg);

			send(new_socket , msg , strlen(msg) , 0);
		}
	}
	return 0;
}