#include<iostream>
#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
int main(int argc , char *argv[])
{	
WSADATA wsa ;
SOCKET s , new_socket;
struct sockaddr_in server , client;
int c, cnt;
char msg1 [100];
char client_reply[2000];
int recv_size;
long int rp, rq, rn, rt, rflag, re[100], rd[100], rtemp[100], rj, rm[100], ren[100], ri;
char msg[2000];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
FILE *fptr;
FILE *txt;
int rc;
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
while(1){
if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
    puts("recv failed");
else { 
client_reply[recv_size] = '\0';
puts(client_reply);
printf ("Me: ");
gets (msg1);
fptr= fopen("pic.jpg","r");
	txt= fopen("test1.txt","w");
	if(fptr==NULL)
	{
		printf("Image empty");
		fclose(fptr);
	}
	else
	{
		printf("Success\n");
	}
	do
	{
		rc=fgetc(fptr);
		for(int i=0;i<=7;i++)
		{
			if(rc&(1<<(7-i)))
			{
				fputc('1',txt);
			}
			else
			{
				fputc('0',txt);
			}
		}
	}while(rc!=EOF);
	fclose(fptr);
	fclose(txt);
	txt=fopen("test1.txt","r");
	fgets(msg,100,txt);
    printf("\nTHE DECRYPTED MESSAGE IS\n");
	puts(msg);
send(new_socket , msg1 , strlen(msg) , 0);
}
}
return 0;
}
