#include "pipe_networking.h"
#include <unistd.h>

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

    while (1)
    {
        from_client = server_setup();

        pid_t subserver;
        subserver = fork();
        if(subserver<0){
          perror("fork fail");//output to stderr instead of stdout
          exit(1);
        } else if ( subserver == 0){
            server_connect(from_client);
        }else{

          close(from_client);
          close(to_client);
        }
    }
    remove(WKP);
    return 0;
}
