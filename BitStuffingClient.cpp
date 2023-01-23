#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>

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
	char str[100];
	char flag[]="01111110";
	int i, j,count=0,nl;

    printf ("Installing");
	for (cnt = 1; cnt <= 3; cnt++)
	{
		timer (1);
		printf (".");
	}

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
		printf ("Me: ");
		gets (str);

		char msg[1000]="01111110";
		//Bit Stuffing

		for (i=0;i<strlen(str);i++) 
		{
		count=0;
		for (j=i;j<(i+5);j++) 
		{
			if(str[j]=='1') 
			{
				count++;
			}
		}

		if(count>=5) {
			nl=strlen(str)+2;
			for (;nl>=(i+5);nl--) {
				str[nl]=str[nl-1];
			}
			str[i+5]='0';
			i=i+7;
		}
	}
	printf("After bit stuffing: %s\n",str);

		//Concatenation
		strcat(msg,str);
		strcat(msg,flag);
		printf("Message to be sent: %s\n\n",msg);

		//Sending message
		send(sck , msg , strlen(msg) , 0);


		if((recv_size = recv(sck , server_reply , 2000 , 0)) == SOCKET_ERROR)
			puts("recv failed");
		else
		{ 
			server_reply[recv_size] = '\0';
			printf("Server reply:");
			puts(server_reply);
			printf("\n");
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


