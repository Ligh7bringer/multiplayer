#include <stdio.h>
#include <winsock2.h>

#include "constants.hpp"

int main()
{
    // Init winsock
    constexpr WORD winsock_version = 0x202;
    WSADATA winsock_data;
    if (WSAStartup(winsock_version, &winsock_data)) {
        printf("WSAStartup failed: %d", WSAGetLastError());
        return 1;
    }

    // Create a socket
    constexpr int address_family = AF_INET; // IPv4
    constexpr int sock_type = SOCK_DGRAM; // UDP socket
    constexpr int protocol = IPPROTO_UDP;
    SOCKET sock = socket(address_family, sock_type, protocol);
    if (sock == INVALID_SOCKET) {
        printf("socket() failed: %d", WSAGetLastError());
        return 1;
    }

    SOCKADDR_IN server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    char message[SOCKET_BUFFER_SIZE];
    gets_s(message, SOCKET_BUFFER_SIZE);

    constexpr int flags = 0;
    if (sendto(sock, message, strlen(message), flags, (SOCKADDR*)&server_address, sizeof(server_address)) == SOCKET_ERROR) {
        printf("sendto() failed: %d", WSAGetLastError());
        return 1;
    }

    WSACleanup();
    return 0;
}
