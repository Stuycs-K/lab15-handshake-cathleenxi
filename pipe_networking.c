#include "pipe_networking.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  int wkp = mkfifo(WKP, 0666); // making WKP
  if (wkp < 0)
  {
    printf("ERROR IN SERVER SETUP [MKFIFO], %s", strerror(errno));
    exit(1);
  }
  int from_client = open(WKP, O_RDONLY);
  if (from_client < 0)
  {
    printf("ERROR IN SERVER SETUP [OPEN], %s", strerror(errno));
    exit(1);
  }

  remove(WKP);
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
  // READING SYN
  int from_client = server_setup();
  char PP[100];
  int reading = read(from_client, PP, 100);
  if (reading < 0)
  {
    printf("ERROR ON READING SYN: %s", strerror(errno));
  }

  // SENDING SYNACK
  *to_client = open(PP, O_WRONLY);

  //srand(time(NULL));
  //int SYNACK = rand();
  int SYNACK = 1;
  printf("SYNACK: %d\n", SYNACK);

  write(*to_client, &SYNACK, sizeof(SYNACK));

  // CHECKING ACK
  char buff[100];
  int rdBytes = read(from_client, buff, 100);
  if (rdBytes < 0)
  {
    printf("%s", strerror(errno));
    exit(1);
  }
  int ack;
  sscanf(buff, "%d", &ack);
  if (ack == SYNACK + 1)
  {
    printf("Three-way handshake has been completed\n");
    return from_client;
  }
  printf("Recieved %d. ACK does not match SYNACK\n", ack);
  return 0;
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
  char PP[] = "toClient";
  int wkp = mkfifo(PP, 0666);

  *to_server = open(WKP, O_WRONLY);
  int writing = write(*to_server, PP, strlen(PP) + 1);
  if (writing < 0)
  {
    printf("ERROR IN CLIENT HANDSHAKE, %s", strerror(errno));
  }
  int from_server = open(PP, O_RDONLY);
  remove(PP);

  char buff[100];
  int reading = read(from_server, buff, 100);
  int ack;
  sscanf(buff, "%d", &ack);
  printf("client ack: %d\n", ack);
  ack += 1;
  //printf("client ack: %dsp", ack);

  char buff2[100];
  sprintf(buff2, "%d", ack);
  printf("client writing %s\n", buff2);
  int writing2 = write(*to_server, buff2, sizeof(ack));
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
