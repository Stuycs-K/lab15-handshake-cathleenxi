#include "pipe_networking.h"

int main()
{

  int to_server;   // WKP
  int from_server; // PP

  from_server = client_handshake(&to_server);

  while(1){
    open(from_server, O_RDONLY);
    char buff[100];
    int numbytes = read(from_server, buff, 100);
    if(numbytes == 0){
      printf("Read 0 bytes, Pipe closed\n");
      break;
    }
    if(numbytes == -1){
      printf(strerror(errno));
    }

    printf("Random number recieved: %s\n", buff);
    char str[100] = "hello from client\n";
    write(to_server, str, sizeof(str));

  }
//  char str[100] = "hello from client\n";
//  write(to_server, str, sizeof(str));
  //sleep(5);
}
