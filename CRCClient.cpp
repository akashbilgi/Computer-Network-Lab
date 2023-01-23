#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include <string.h>
#define N strlen(g)

#pragma comment (lib, "ws2_32.lib")
void timer (int);
char t[28],cs[28],g[]="1011";
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
	WSADATA wsa;
	SOCKET sck;
	int cnt;
	struct sockaddr_in ip_info;
	char server_reply[2000];
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
		int recv_size;
		char msg[1000];
		char str[100];

		printf ("Me: ");
		gets (str);
		int flag1=0;

		//Bit Stuffing
		int val=strlen(str);
		for (i=0;i<val;i++)
		{
			if(str[i]=='1'||str[i]=='0') 
			{
				flag1=0;
			}
			else 
				flag1= 1;

		}
		if(flag1==0)
		{
			for (i=0;i<val;i++) 
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
			i=i+5;
			val+=1;
		}
	}
	printf("After bit stuffing: %s\n",str);
	strcpy(t,str);
	a=strlen(t);
    for(e=a;e<a+N-1;e++)
        t[e]='0';
	 printf("\n----------------------------------------");
    printf("\nModified data is : %s",t);
	crc();
	for(e=a;e<a+N-1;e++)
        t[e]=cs[e-a];
	
	printf("\nCRC: %s", t);

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

		strcpy(str,t);

    }
	else
	{
	strcpy(str,t);
	}
		//Concatenation
		strcpy(msg,flag);
		strcat(msg,str);
		strcat(msg,flag);
		
		printf("\nThe msg to be sent: %s\n",msg);
		

		//Sending message
		send(sck , msg , strlen(msg) , 0);

		if((recv_size = recv(sck , server_reply , 2000 , 0)) == SOCKET_ERROR)
			puts("recv failed");
		else
		{ 
			server_reply[recv_size] = '\0';
			puts(server_reply);

		}

	}
		else
		{
			printf("\nSorry ur msg contains illegal characters please enter again\n");
			//gets(str);
		}
	}
	return 0;
}

// Timer function: 
void timer (int sec)
{
	clock_t end;
	end = clock () + sec * CLOCKS_PER_SEC;
	while (clock () <= end);
}