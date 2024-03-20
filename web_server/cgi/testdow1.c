#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT 8696
#define FILENAME "test.txt"

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // 创建socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("192.168.62.11");
    address.sin_port = htons(PORT);

    // 绑定IP和端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // 监听端口
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // 接受连接
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        // 读取HTTP请求
        read(new_socket, buffer, 1024);
        printf("%s\n", buffer);

        // 发送HTTP响应
        char *response = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Disposition: attachment; filename=test.txt\n\n";
        send(new_socket, response, strlen(response), 0);

        // 打开文件并发送内容
        int file_fd = open(FILENAME, O_RDONLY);
        if (file_fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        int bytes_read;
        while ((bytes_read = read(file_fd, buffer, sizeof(buffer))) > 0) {
            send(new_socket, buffer, bytes_read, 0);
        }

        close(file_fd);
        close(new_socket);
    }

    return 0;
}
