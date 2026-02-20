// C++ Backend - Simple HTTP Server
// Compile: g++ -o server main.cpp -lws2_32
// Run:     server.exe
// Note:    -lws2_32 links the Windows Socket library (Winsock)
//          On Linux/Mac: g++ -o server main.cpp (no extra flag needed)

#include <iostream>
#include <string>
#include <winsock2.h>   // Windows socket library
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8083

std::string buildResponse(std::string body) {
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n"   // Allow CORS
        "Connection: close\r\n"
        "\r\n" +
        body;
    return response;
}

int main() {
    // Step 1: Initialize Winsock (Windows only requirement)
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    // Step 2: Create socket
    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    // Step 3: Bind to port
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    // Step 4: Listen for connections
    listen(serverSocket, 5);
    std::cout << "C++ server running on http://localhost:" << PORT << std::endl;
    std::cout << "Press Ctrl+C to stop." << std::endl;

    // Step 5: Accept and handle requests in a loop
    while (true) {
        SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);

        // Read the HTTP request (we don't need to parse it fully for this demo)
        char buffer[4096] = {0};
        recv(clientSocket, buffer, sizeof(buffer), 0);

        std::string request(buffer);

        // Check if it's a GET /hello request
        std::string responseBody;
        if (request.find("GET /hello") != std::string::npos) {
            responseBody = "{\"message\": \"Hello World! From C++!\"}";
        } else {
            responseBody = "{\"error\": \"Not found\"}";
        }

        std::string response = buildResponse(responseBody);

        // Send response back to client
        send(clientSocket, response.c_str(), response.size(), 0);
        closesocket(clientSocket);
    }

    // Cleanup (unreachable in this demo but good practice)
    closesocket(serverSocket);
    WSACleanup();
    return 0;
}