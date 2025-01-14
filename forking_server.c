#include "pipe_networking.h"
#include <time.h>
void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\nSIGINT received. Cleaning up and exiting...\n");
    remove(WKP); // Remove the well-known pipe
    exit(0);
  }
}

int main()
{
  int to_client;   // PP
  int from_client; // WKP

  signal(SIGINT, sighandler);

  srand(time(NULL));
  // printf("outside loop\n");
  while (1)
  {
//    printf("inside loop\n");
    from_client = server_setup();
    pid_t subserver = fork();
    if (subserver == 0)
    {
      server_handshake_half(&to_client, from_client);

      int num = rand();
      char buff[100];
      sprintf(buff, "%d", num);
      //    printf("abt to open\n");
      int fd = open(to_client, O_WRONLY);
      //  printf("opened\n");
      // if(fdprintf(strerror(errno))

      //  printf("abt to write\n");
      write(to_client, buff, sizeof(buff));
      //  printf("abt to sleep\n");
      sleep(1);
      printf("wrote and slept\n");
      close(from_client);
      close(to_client);
    }
  }
  remove(WKP);
  return 0;
}
