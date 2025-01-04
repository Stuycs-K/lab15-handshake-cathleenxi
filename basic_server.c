#include "pipe_networking.h"

int main() {
  int to_client = server_setup();
  int from_client;

  from_client = server_handshake( &to_client );
}
