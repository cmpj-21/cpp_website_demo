# Build Stage
FROM alpine:latest AS builder

# Install build dependencies
RUN apk add --no-cache g++ make

# Set working directory
WORKDIR /app

# Copy source code
COPY main.cpp .

# Compile the app
RUN g++ -o server main.cpp

# Final Stage
FROM alpine:latest

# Install runtime dependencies for C++
RUN apk add --no-cache libstdc++ libgcc

# Set working directory
WORKDIR /app

# Copy the compiled executable from the builder stage
COPY --from=builder /app/server .

# Expose the port the app runs on
EXPOSE 8083

# Run the application
CMD ["./server"]
