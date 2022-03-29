#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 80

int main(int argc, char const *argv[]) {
  if(argc <= 0) {
    printf("Target website not specified");
    return -1;
  }

  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char* str = "HEAD / HTTP/1.1";
  char buffer[1024] = {0};

  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  if(inet_pton(AF_INET, argv[0], &serv_addr.sin_addr) <= 0) {
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
