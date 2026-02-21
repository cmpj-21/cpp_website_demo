# C++ Website Demo

A simple HTTP server built in C++ that serves a JSON response to a frontend.

## How to Run

### 1. Build with CMake (Recommended)
```powershell
mkdir build
cd build
cmake ..
cmake --build .
```
The executable will be named `app` (or `app.exe` on Windows) inside the `build` or `build/Debug` folder.

### 2. Manual Compilation (Alternative)
```powershell
g++ -o server main.cpp -lws2_32
```

## How to Run

### 1. Run the Server
- If built with **CMake**: run `build/app.exe` (or `./app` on Linux).
- If built **manually**: run `./server.exe`.

### 3. Open the Frontend
Simply open `index.html` in your browser. The frontend will communicate with the C++ server running on port `8083`.

---

## Running with Docker

If you have Docker installed, you can run the entire backend without needing a local compiler.

### 1. Build and Run
```powershell
docker-compose up --build
```

### 2. Stop
```powershell
docker-compose down
```

## Features
- Minimalist C++ HTTP Server using Winsock (Windows) and POSIX (Linux).
- Dockerized setup for cross-platform deployment.
- JSON API endpoint (`/hello`).
- Vanilla HTML/JS frontend.
