#include "pipe_networking.h"
#include <unistd.h>
#include <stdio.h>
// UPSTREAM = to the server / from the client || WKP
// DOWNSTREAM = to the client / from the server || PP
/*=========================
  server_setup

  creates the WKP and opens it, waiting for a  connection.
  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup()
{
  int from_client = mkfifo("toServer", 0666); // making WKP
  if (from_client < 0)
  {
    printf("%s", strerror(errno));
    exit(1);
  }
  int readfd = open("toServer", O_RDONLY);
  char buff[100];
  while (1)
  {
    int bytesread = read(readfd, buff, 100);
    if (bytesread < 0)
    {
      printf("%s", strerror(errno));
      exit(1);
    }
    if (bytesread != 0)
      break;&to_client );
}
  }
  remove("toServer");
  return from_client;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe (Client's private pipe).

  returns the file descriptor for the upstream pipe (see server setup).
  =========================*/
int server_handshake(int *to_client)
{
  *to_client = open("toClient", O_WRONLY);

   srand(time(NULL));
   int SYN_ACK = rand();

   write(to_client,SYN_ACK, sizeof(SYN_ACK));

  int from_client = open("toServer", RDONLY);
  char buff[100];
  int rdBytes = read(from_client, buff,100);
  if (rdBytes < 0){
    printf("%s", strerror(errno));
    exit(1);
  }
  int ACK;
  sscanf(buff, "%d", &ACK);
  if(ACK == SYN_ACK + 1){
    
  }
  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server)
{
  int from_server;
  return from_server;
}

/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client)
{
  int to_client = 0;
  return to_client;
}
