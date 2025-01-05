#include "pipe_networking.h"

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
        from_client = server_handshake(&to_client);
        close(from_client);
        close(to_client);
    }
    remove(WKP);
    return 0;
}