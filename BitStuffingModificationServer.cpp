#include<io.h>
#include<stdio.h>
#include<iostream>
using namespace std;
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#define N strlen(g)
using namespace std;
#pragma comment (lib, "ws2_32.lib")
void timer (int);
void ShowByte( char b , FILE * im);
char t[1000],cs[1000],g[]="111110000001001";
int a,e,c;
 void xor(){
    for(c = 1;c < N; c++)
    cs[c] = (( cs[c] == g[c])?'0':'1');
}
 void crc(){
    for(e=0;e<N;e++)
        cs[e]=t[e];
    do{
        if(cs[0]=='1')
            xor();
        for(c=0;c<N-1;c++)
            cs[c]=cs[c+1];
        cs[c]=t[e++];
    }while(e<=a+N-1);
}
int main(int argc , char *argv[])
{

WSADATA wsa ;
SOCKET s , new_socket;
struct sockaddr_in server , client;
int c, cnt;
char msg [1000];
char client_reply[2000];
int recv_size;
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
printf ("message is : ");
 cout<<client_reply<<endl;
printf ("ME: ");
cin>>msg;
send(new_socket , msg , strlen(msg) , 0);
}
}
return 0;
}

