#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#define PORT 80

int hostname_to_ip(char *, char *);

int main(int argc, char const *argv[]) {
  if(argc <= 1) {
    printf("Target website not specified\n\n");
    return -1;
  }


  char *hostname = strdup(argv[1]);
  char ip[100];

  hostname_to_ip(hostname, ip);

  printf("%s resolved to %s\n", hostname, ip);

  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char* str = "GET / HTTP/1.1\r\nHost: athena.haunui.ovh\r\nUser-Agent: curl/7.74.0\r\nAccept: */*\r\n\r\n";
  char buffer[1024] = {0};

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address/ Address not supported \n");
    return -1;
  }

  if(connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    return -1;
  }

  send(sock, str, strlen(str), 0);
  printf("HTTP req. sent\n");
  valread = read(sock, buffer, 1024);
  printf("%s\n", buffer);
  return 0;
}

int hostname_to_ip(char * hostname , char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ( (he = gethostbyname( hostname ) ) == NULL)
	{
		// get the host info
		printf("gethostbyname");
		return 1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		//Return the first one;
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}

	return 1;
}
