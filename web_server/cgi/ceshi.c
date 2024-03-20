#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
	printf("准备接收链接\n");
    // 创建套接字
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("套接字创建失败\n");
        exit(EXIT_FAILURE);
    }

	
    // 设置服务器地址
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("192.168.62.11");
    server_addr.sin_port = htons(8696);

    // 绑定套接字
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("绑定失败\n");
        exit(EXIT_FAILURE);

    }

   //设端口复用
	int val =1;
	setsockopt(server_fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));	

    // 监听连接
    if (listen(server_fd, 10) < 0) {
        perror("监听失败\n");
        exit(EXIT_FAILURE);
    }
	
    // 接受连接
    int client_fd;
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    char buffer[1024] = "";

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len);
        if (client_fd < 0) {
            perror("连接建立失败\n");
            exit(EXIT_FAILURE);
        }else
	printf("链接成功\n");
        // 读取请求
	memset(buffer,0x00,sizeof(buffer));
        read(client_fd, buffer, 1024);
        printf("buf值: %s\n", buffer);

        // 处理请求
//        if(strstr("POST",buffer)>0)
//		{
			char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\n\nHello, your message has been received and processed.";
//		 } 
        

        // 发送响应
       send(client_fd, response, strlen(response), 0);
       printf("Response sent.\n");

        // 关闭连接
        close(client_fd);
    }
	close(server_fd);

    return 0;
}

