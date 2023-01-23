#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#pragma comment (lib, "ws2_32.lib")
void timer (int);

int main (int argc, char *argv [])
{
	WSADATA wsa;
	SOCKET sck;
	int cnt;
	struct sockaddr_in ip_info;
	char server_reply[2000];
	int recv_size;
	char msg[100]="";
	int m;
	int frames;
	int z=0;
	int seqnum;
	char channel[] = "1";
	int arr[100];
	int a;
	int y=0;
	char done[]="done";
	int choice;

	printf ("Installing...");

	if (WSAStartup (MAKEWORD (2,2), &wsa) == INVALID_SOCKET)
		printf ("WSA error\n");
	else
		if ((sck = socket (AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
			printf ("Socket error\n");
		else
		{
			ip_info.sin_addr.s_addr = inet_addr("127.0.0.1");
			ip_info.sin_family = AF_INET;
			ip_info.sin_port = htons (8888);
		}

	if (connect (sck, (struct sockaddr *)&ip_info, sizeof (ip_info)) < 0)
		printf ("\nNot connected\n");
	else
		printf ("\nSession is up\n");

	while(1)
	{
		printf("Enter 0 to exit");

	start: printf("Checking if the channel is busy...\n");
	send(sck , channel , strlen(channel) , 0);
	if((recv_size = recv(sck , msg , 2000 , 0)) == SOCKET_ERROR)
	{
		puts("recv failed");
	}
	else 
	{
		msg[recv_size] = '\0';
		if(strcmp(msg,"0")==0)
		{
			printf("Channel Busy\n");
			goto start;
		}
	}

xy : printf("Channel is idle\n");
	printf("Enter the sequence numbers:");
	scanf("%d",&seqnum);
	for( a=0; a<seqnum; a++)
	{
		arr[a] = a;
	}
	bb: printf("Enter a Window size:");
	try
	{
		scanf("%d",&m);
		if(m > seqnum || m<=0)
		{
			throw 5;
		}
	}
	catch(int i)
	{
		printf("Window size should be less than sequence number.\n");
		goto bb;
	}
	msg[0]=m+'0';
	msg[1]='\0';
	send(sck , msg , strlen(msg) , 0);

	xx: while(1)
	{
			for(int d=0;d<m;d++)
			{

				if(y>=seqnum)
				{
					goto aa;
				}
				printf("Sending frame %d\n", y);
				msg[0] = arr[y]+'0';
				y++;
				msg[1] = '\0';
				send(sck , msg , strlen(msg) , 0);

				if((recv_size = recv(sck , server_reply , 2000 , 0)) == SOCKET_ERROR)
				{
					puts("Recv failed");
					timer(2);
					if((recv_size = recv(sck , server_reply , 2000 , 0)) == SOCKET_ERROR)
					{
						puts("Recv failed");
						y=y-2;
						goto xx;   
					}
					else
					{
						server_reply[recv_size] = '\0';
						if(server_reply == "Message not received")
						{
							printf("Message not acknowledged");
							y=y-2;
							goto xx;
						}
						else
						{
							puts(server_reply);
						
						}
					}
				}		
				else 
				{ 
					server_reply[recv_size] = '\0';
					if(server_reply == "Message not received")
					{
						printf("Message not acknowledged");
						y=y-2;
						goto xx;
						//z=z-m;
					}
					else
					{
						puts(server_reply);
						
					}
				}
			}
			printf("**************************************\n");
	}
aa: printf("Message is sent completely\n");
	send(sck , done , strlen(done) , 0);
	}
	system("pause");
	return 0;
}

// Timer function: 
void timer (int sec)
{
	clock_t end;

	end = clock () + sec * CLOCKS_PER_SEC;
	while (clock () <= end);
}