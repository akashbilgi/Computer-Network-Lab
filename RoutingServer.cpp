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
char msg [100];
char client_reply[2000];
int recv_size;
int path[100][100];

int count,src_router,i,j,k,w,v,min;
int cost_matrix[100][100],dist[100],last[100];
int flag[100];
int snd;
int z,x=0;

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
	printf("\n Enter the no of routers");
	scanf("%d",&count);

	printf("\n Enter the cost matrix values:");
	for(i=0;i<count;i++)
	{
		for(j=0;j<count;j++)
		{
			printf("\n%d->%d:",i,j);
			scanf("%d",&cost_matrix[i][j]);
			if(cost_matrix[i][j]<0)
				cost_matrix[i][j]=1000;
		}
	}
	printf("\n Enter the source router:");
	scanf("%d",&src_router);

	msg[0] = src_router + '0';
	msg[1] = '\0';

	send(new_socket , msg , strlen(msg) , 0);

	for(v=0;v<count;v++)
	{
		flag[v]=0;
		last[v]=src_router;
		dist[v]=cost_matrix[src_router][v];
	}
	flag[src_router]=1;
	for(i=0;i<count;i++)
	{
		min=1000;
		for(w=0;w<count;w++)
		{
			if(!flag[w])
			if(dist[w]<min)
			{
				v=w;
				min=dist[w];
			}
		}
		flag[v]=1;
		for(w=0;w<count;w++)
		{
			if(!flag[w])
			if(min+cost_matrix[v][w]<dist[w])
			{
				dist[w]=min+cost_matrix[v][w];
				last[w]=v;
			}
		}
	}
	for(i=0;i<count;i++)
	{
		x=0;
		printf("\n%d==>%d:Path taken:%d",src_router,i,i);
		w=i;
		path[i][x] = i;
		x++;
		while(w!=src_router)
		{
			printf("\n<--%d",last[w]);
			path[i][x] = last[w];
			x++;
			w=last[w];
		}
		printf("\n Shortest path cost:%d\n",dist[i]);

		snd=dist[i];
	}

	for(z=0; z<count; z++)
	{
		msg[z] = dist[z] + '0';
	}
	msg[z] = '\0';

	send(new_socket , msg , strlen(msg) , 0);

	if((recv_size = recv(new_socket , client_reply , 2000 , 0)) == SOCKET_ERROR)
		puts("recv failed");
	else 
	{ 
		client_reply[recv_size] = '\0';
		printf("Reply: ");
		puts(client_reply);
		printf("\n");
	}
}
return 0;
}