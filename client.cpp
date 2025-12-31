#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in server;
    char message[1024];
    char reply[1024];

    WSAStartup(MAKEWORD(2,2), &wsa);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(5555);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&server, sizeof(server));

    while (true) {
        std::cout << "Send> ";
        std::cin.getline(message, sizeof(message));

        send(sock, message, strlen(message), 0);

        int recvSize = recv(sock, reply, sizeof(reply), 0);
        reply[recvSize] = '\0';

        std::cout << "Echo> " << reply << "\n";
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
