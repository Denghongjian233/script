#include <iostream>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

void receive_messages(int client_socket)
{
    char buffer[BUFFER_SIZE];
    while (true)
    {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            std::cerr << "Connection closed." << std::endl;
            close(client_socket);
            exit(1);
        }
        buffer[bytes_received] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }
}

int main()
{
    int client_socket;
    struct sockaddr_in server_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Connection failed." << std::endl;
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    // 使用 lambda 捕获 client_socket，并传递给线程函数
    std::thread t(receive_messages, client_socket);
    t.detach();

    char buffer[BUFFER_SIZE];
    while (true)
    {
        std::cin.getline(buffer, BUFFER_SIZE);
        send(client_socket, buffer, strlen(buffer), 0);
    }

    close(client_socket);
    return 0;
}
