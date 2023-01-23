#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<string.h>
#include<ctime>
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
int main (int argc, char *argv [])
{
    string hh;
  FILE * pFile;
  FILE * image;
  int c;
  pFile=fopen ("butterfly.jpg","r");
  image=fopen ("1.txt","w");
  if (pFile==NULL) perror ("Error opening file");
  else
  {

      c = fgetc(pFile);
      while (c != EOF)
    {
              ShowByte((char)c, image);
         c = fgetc(pFile);
    }
        }
    fclose (pFile);
     fclose (image);
WSADATA wsa;
SOCKET sck;
int cnt;
struct sockaddr_in ip_info;
char server_reply[2000];
int recv_size;
int i, j,k,count=0,nl=0;
printf ("Installing");
for (cnt = 1; cnt <= 3; cnt++){
timer (1);
printf (".");
}
if (WSAStartup (MAKEWORD (2,2), &wsa) == INVALID_SOCKET)
printf ("WSA error\n");
else
if ((sck = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
printf ("Socket error\n");
else{
ip_info.sin_addr.s_addr = inet_addr("127.0.0.1");
ip_info.sin_family = AF_INET;
ip_info.sin_port = htons (8888);
}
if (connect (sck, (struct sockaddr *)&ip_info, sizeof (ip_info)) < 0)
printf ("\nNot connected\n");
else
printf ("\nSession is up\n");
char msg[1000];
while(1){
    ifstream image2("1.txt");
    while(!image2.eof())
    {
        image2>>msg;
    }
	cout<<msg<<endl;
	cout<<"The length of message before stuffed is \n"<<endl;
	cout<<strlen(msg)<<endl;
	int start_o=clock();
count=0;
  int a;
	cout<<"Enter the position where number of 0's  to be inserted \n"<<endl;
	cin>>a;
for (i=0;i<strlen(msg);i++) {
     if(msg[i]=='0')
    {
        count = 0;
    }
   else if(msg[i]=='1')
    {
        count = count + 1;
    }
    else
    {
        printf("Wrong input\n");
        
    }
    if(count == a)
    {

        for(j=(strlen(msg)+1);j>i+1;j--)
        {
            msg[j] = msg[j-1];
        }
        msg[i+1]= '0';
    }
 }
     printf("After stuffing:\n");
    cout<<(msg);
	int stop_o=clock();
	cout<<"\n The overhead cost is \n"<<endl;
	cout<<(stop_o-start_o)/double(CLOCKS_PER_SEC)*1000<<endl;
	cout<<"\n The length of message after stuffed is \n"<<endl;
	cout<<strlen(msg)<<endl;
	for(int j=0;j<=strlen(msg);j++)
	{
		t[j]=msg[j];
	}
	printf("\n----------------------------------------");
    printf("\nGeneratng polynomial : %s",g);
    a=strlen(t);
    for(e=a;e<a+N-1;e++)
        t[e]='0';
    printf("\n----------------------------------------");
    printf("\nModified data is : %s",t);
    printf("\n----------------------------------------");
    crc();
    printf("\nChecksum is : %s",cs);
    for(e=a;e<a+N-1;e++)
        t[e]=cs[e-a];
    printf("\n----------------------------------------");
    printf("\nFinal codeword is : %s",t);
    printf("\n----------------------------------------");
    printf("\nTest error detection 0(yes) 1(no)? : ");
    scanf("%d",&e);
    if(e==0)
    {
        do{
            printf("\nEnter the position where error is to be inserted : ");
            scanf("%d",&e);
        }while(e==0 || e>a+N-1);
        t[e-1]=(t[e-1]=='0')?'1':'0';
        printf("\n----------------------------------------");
        printf("\nErroneous data : %s\n",t);
    }
    crc();
    for(e=0;(e<N-1) && (cs[e]!='1');e++);
        if(e<N-1)
            printf("\nError detected\n\n");
        else
		{
			cout<<"No error detected"<<endl;
			send(sck , t , strlen(msg) , 0);
		}
            send(sck , t , strlen(msg) , 0);
if((recv_size = recv(sck , server_reply , 2000 , 0)) == SOCKET_ERROR)
    puts("recv failed");
else { 
server_reply[recv_size] = '\0';
puts(server_reply);
}
}
getch ();
return 0;
}
// Timer function: 
void timer (int sec)
{
clock_t end;
end = clock () + sec * CLOCKS_PER_SEC;
while (clock () <= end);
}
void ShowByte( char b , FILE * im)
{
    int i;
    for( i = 7; i >= 0; --i)
    {
        if ( b & (1 << i) )
        {
              fputc('1', im);
        }
        else
        {
              fputc('0', im);
        }
   }
}
