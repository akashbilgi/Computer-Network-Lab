#include <stdio.h>
#include <conio.h>
#include <winsock2.h>
#include <time.h>
#include<iostream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
 long int p, q, n, t, flag, e[100], d[100], temp[100], j, m[100], en[100], i;
char msg[2000];
int prime(long int);
void ce();
long int cd(long int);
void encrypt();
void decrypt();
FILE *fptr;
FILE *txt;
int c;
int prime(long int pr)
{
    int i;
    j = pow(pr, 0.5);
    for (i = 2; i <= j; i++)
    {
        if (pr % i == 0)
            return 0;
    }
    return 1;
}
void timer (int);
int main (int argc, char *argv [])
{	
WSADATA wsa;
SOCKET sck;
int cnt;
struct sockaddr_in ip_info;
char server_reply[2000];
int recv_size;
char msg1[100];
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
while(1){
printf ("Me: ");
gets (msg1);
send(sck , msg1 , strlen(msg1) , 0);
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
c=fgetc(fptr);
for(int i=0;i<=7;i++)
{
if(c&(1<<(7-i)))
{
fputc('1',txt);
}
else
{
fputc('0',txt);
}
}
}while(c!=EOF);
fclose(fptr);
fclose(txt);
txt=fopen("test1.txt","r");
fgets(msg,100,txt);
cout << "\nENTER FIRST PRIME NUMBER\n";
cin >> p;
flag = prime(p);
if (flag == 0)
{
 cout << "\nWRONG INPUT\n";
 exit(1);
}
cout << "\nENTER ANOTHER PRIME NUMBER\n";
cin >> q;
flag = prime(q);
if (flag == 0 || p == q)
{
  cout << "\nWRONG INPUT\n";
  exit(1)
}
cout << "\n MESSAGE\n";
cout<< msg;
fflush(stdin);
for (i = 0; msg[i] != NULL; i++)
m[i] = msg[i];
n = p * q;
t = (p - 1) * (q - 1);
ce();
cout << "\nPOSSIBLE VALUES OF e AND d ARE\n";
for (i = 0; i < j - 1; i++)
cout << e[i] << "\t" << d[i] << "\n";
encrypt();
decrypt();
return 0;
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
void ce()
{
    int k;
    k = 0;
    for (i = 2; i < t; i++)
    {
        if (t % i == 0)
            continue;
        flag = prime(i);
        if (flag == 1 && i != p && i != q)
        {
            e[k] = i;
            flag = cd(e[k]);
            if (flag > 0)
            {
                d[k] = flag;
                k++;
            }
            if (k == 99)
                break;
        }
    }
}
long int cd(long int x)
{
long int k = 1;
    while (1)
    {
        k = k + t;
        if (k % x == 0)
            return (k / x);
    }
}
void encrypt()
{
    long int pt, ct, key = e[0], k, len;
    i = 0;
    len = strlen(msg);
    while (i != len)
    {
        pt = m[i];
        pt = pt - 96;
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * pt;
            k = k % n;
        }
        temp[i] = k;
        ct = k + 96;
        en[i] = ct;
        i++;
    }
    en[i] = -1;
    cout << "\nTHE ENCRYPTED MESSAGE IS\n";
    for (i = 0; en[i] != -1; i++)
        printf("%c", en[i]);
}
void decrypt()
{
    long int pt, ct, key = d[0], k;
    i = 0;
    while (en[i] != -1)
    {
        ct = temp[i];
        k = 1;
        for (j = 0; j < key; j++)
        {
            k = k * ct;
            k = k % n;
        }
        pt = k + 96;
        m[i] = pt;
        i++;
    }
    m[i] = -1;
    cout << "\nTHE DECRYPTED MESSAGE IS\n";
	cout<< msg;
	system("pause");
}
// Timer function: 
void timer (int sec)
{
clock_t end;
end = clock () + sec * CLOCKS_PER_SEC;
while (clock () <= end);
}
