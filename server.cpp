#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsa;
    SOCKET serverSock, clientSock;
    sockaddr_in serverAddr, clientAddr;
    int clientSize = sizeof(clientAddr);
    char buffer[1024];

    WSAStartup(MAKEWORD(2,2), &wsa);

    serverSock = socket(AF_INET, SOCK_STREAM, 0);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(5555);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSock, 1);

    std::cout << "Server listening on port 5555...\n";

    clientSock = accept(serverSock, (sockaddr*)&clientAddr, &clientSize);
    std::cout << "Client connected\n";

    int bytes;
    while ((bytes = recv(clientSock, buffer, sizeof(buffer), 0)) > 0) {
        send(clientSock, buffer, bytes, 0);
    }

    closesocket(clientSock);
    closesocket(serverSock);
    WSACleanup();

    return 0;
}
