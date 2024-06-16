
#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

std::vector<int> clients;

void handle_client(int client_socket)
{
    char buffer[BUFFER_SIZE];
    while (true)
    {
        int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytes_received <= 0)
        {
            std::cerr << "Client disconnected: " << client_socket << std::endl;
            close(client_socket);
            clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
            break;
        }
        buffer[bytes_received] = '\0';
        std::cout << "Client " << client_socket << ": " << buffer << std::endl;

        for (int client : clients)
        {
            if (client != client_socket)
            {
                send(client, buffer, bytes_received, 0);
            }
        }
    }
}

int main()
{
    int server_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        std::cerr << "Bind failed." << std::endl;
        return 1;
    }

    if (listen(server_socket, 3) < 0)
    {
        std::cerr << "Listen failed." << std::endl;
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    while (true)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_len);
        if (client_socket < 0)
        {
            std::cerr << "Accept failed." << std::endl;
            continue;
        }

        std::cout << "New client connected: " << client_socket << std::endl;
        clients.push_back(client_socket);

        std::thread(handle_client, client_socket).detach();
    }

    close(server_socket);
    return 0;
}
