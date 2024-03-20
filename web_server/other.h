#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/tcp.h>
#pragma once

void Qcheat(char *text);//聊天头文件
void cmd(char *text,int client_socket);//CMD命令程序头文件 
void messages(int client_socket,char *buffer);//消息处理 
void addSocket(int newSocket);//添加群成员套接字 
void removeSocket(int socketToRemove);//去除群聊成员套接字 
void message(char *message,int client_socket);//群发函数 
void examination(char *text,int client_socket);//考试函数

typedef struct{
    int socket;
    struct sockaddr_in address;
    int active;
}client_t;


