#include<io.h>
#include<stdio.h>
#include<winsock2.h>
#define N strlen(g)
#pragma comment(lib,"ws2_32.lib") //Winsock Library

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

int main(int argc , char *argv[])
{

	WSADATA wsa ;
	SOCKET s , new_socket;
	struct sockaddr_in server , client;
	int c, cnt;
	char msg [100];
	char client_reply[2000], original_msg[1000];
	int recv_size;
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
		count =0;

		if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
			puts("recv failed");
		else 
		{ 
			client_reply[recv_size] = '\0';
			printf("Message received from client: ");
			puts(client_reply);
			int m=0;
			for(i=8;i<strlen(client_reply)-8;i++)
			{
				t[m]=client_reply[i];
				m++;
			}
			t[m]= '\0';

				//strcpy(t,client_reply);
				a=strlen(t);
				//for(e=a;e<a+N-1;e++)
					//t[e]='0';
				printf("\n----------------------------------------");
				printf("\nModified data is : %s",t);
					crc();
				printf("\n\nThe reminder is: %s",cs);
				int flag1=0;
				for(i=0;i<strlen(cs);i++)
				{
					if(cs[i]=='0')
					{}
					else 
						flag1=1;

				}
				if(flag1==1)
				{
					printf("\nThe message recieved has errors");
					getchar();
					break;
				}
			
				printf("\nSUCCESS, correct msg recieved\n");

			//De-Stuffing
			j=0;
			for(i=8;i<strlen(client_reply)-11;i++)
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
        printf("\nOriginal Message : ");
        puts(original_msg);

		printf ("Server: ");
		gets (msg);

		send(new_socket , msg , strlen(msg) , 0);
		}
	}
	return 0;
}