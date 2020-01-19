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

    // Bind socket
    SOCKADDR_IN local_address;
    local_address.sin_family = AF_INET;
    local_address.sin_port = htons(PORT); // Arbitrary port number
    local_address.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (SOCKADDR*)&local_address, sizeof(local_address)) == SOCKET_ERROR) {
        printf("bind() failed: %d", WSAGetLastError());
        return 2;
    }

    char buffer[SOCKET_BUFFER_SIZE];
    constexpr int flags = 0;
    SOCKADDR_IN from;
    int from_size = sizeof(from);
    int bytes_received = recvfrom(sock, buffer, SOCKET_BUFFER_SIZE, flags, (SOCKADDR*)&from, &from_size);
    if (bytes_received == SOCKET_ERROR) {
        printf("recvfrom() returned SOCKET_ERROR: %d", WSAGetLastError());
    } else {
        buffer[bytes_received] = 0;
        printf("%d.%d.%d.%d.%d - %s", from.sin_addr.S_un.S_un_b.s_b1,
            from.sin_addr.S_un.S_un_b.s_b2,
            from.sin_addr.S_un.S_un_b.s_b3,
            from.sin_addr.S_un.S_un_b.s_b4,
            ntohs(from.sin_port), buffer);
    }

    getchar();
    // Clean up
    WSACleanup();
    return 0;
}
