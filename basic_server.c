#include "pipe_networking.h"

int main()
{
  int to_client;   // PP
  int from_client; // WKP

  from_client = server_handshake(&to_client);
}
