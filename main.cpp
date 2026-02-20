// Cross-Platform C++ Backend - Simple HTTP Server
// Windows Compile: g++ -o server main.cpp -lws2_32
// Linux Compile:   g++ -o server main.cpp

#include <cstring>
#include <iostream>
#include <string>


#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")
typedef int socklen_t;
#define close_socket closesocket
#else
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define close_socket close
typedef int SOCKET;
#define INVALID_SOCKET -1
#endif

#define PORT 8083

std::string buildResponse(std::string body) {
  std::string response = "HTTP/1.1 200 OK\r\n"
                         "Content-Type: application/json\r\n"
                         "Access-Control-Allow-Origin: *\r\n"
                         "Connection: close\r\n"
                         "\r\n" +
                         body;
  return response;
}

int main() {
#ifdef _WIN32
  WSADATA wsaData;
  if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    std::cerr << "Winsock initialization failed." << std::endl;
    return 1;
  }
#endif

  // Create socket
  SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    std::cerr << "Socket creation failed." << std::endl;
    return 1;
  }

#ifndef _WIN32
  // Allow port reuse on Linux (prevents "address already in use" errors)
  int opt = 1;
  setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
#endif

  // Bind to port
  sockaddr_in serverAddr;
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  if (bind(serverSocket, (sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
    std::cerr << "Bind failed." << std::endl;
    return 1;
  }

  // Listen
  if (listen(serverSocket, 5) < 0) {
    std::cerr << "Listen failed." << std::endl;
    return 1;
  }

  std::cout << "Server running on http://localhost:" << PORT << std::endl;
  std::cout << "Press Ctrl+C to stop." << std::endl;

  while (true) {
    SOCKET clientSocket = accept(serverSocket, nullptr, nullptr);
    if (clientSocket < 0)
      continue;

    char buffer[4096] = {0};
#ifdef _WIN32
    recv(clientSocket, buffer, sizeof(buffer), 0);
#else
    read(clientSocket, buffer, sizeof(buffer));
#endif

    std::string request(buffer);
    std::string responseBody;

    if (request.find("GET /hello") != std::string::npos) {
      responseBody = "{\"message\": \"Hello World! From C++!\"}";
    } else {
      responseBody = "{\"error\": \"Not found\"}";
    }

    std::string response = buildResponse(responseBody);
    send(clientSocket, response.c_str(), (int)response.size(), 0);
    close_socket(clientSocket);
  }

  close_socket(serverSocket);
#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}