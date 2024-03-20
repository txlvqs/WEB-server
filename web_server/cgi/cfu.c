#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8696);
    server_address.sin_addr.s_addr = inet_addr("192.168.62.11");

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    listen(server_socket, 5);

    int client_socket;
	printf("等待链接中\n");
    client_socket = accept(server_socket, NULL, NULL);
	printf("链接成功\n");
    char request[1024];
    char response[1024] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nAccess-Control-Allow-Origin: *\r\n";
    char *data = strstr(request, "data=");
    recv(client_socket, request, sizeof(request), 0);
    printf("Received request: %s\n", request);

    if (data) {
        strcat(response, data + 5);
        strcat(response, " hello");
    } else {
        strcat(response, "No data received");
    }
    printf("*************");
    printf("%s",response);
    printf("*************");
    send(client_socket, response, sizeof(response), 0);
    close(server_socket);
    return 0;
}

