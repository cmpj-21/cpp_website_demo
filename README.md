# C++ Website Demo

A simple HTTP server built in C++ that serves a JSON response to a frontend.

## How to Run

### 1. Compile the Backend (Windows)
```powershell
g++ -o server main.cpp -lws2_32
```

### 2. Run the Server
```powershell
./server.exe
```

### 3. Open the Frontend
Simply open `index.html` in your browser. The frontend will communicate with the C++ server running on port `8083`.

## Features
- Minimalist C++ HTTP Server using Winsock.
- JSON API endpoint (`/hello`).
- Vanilla HTML/JS frontend.
