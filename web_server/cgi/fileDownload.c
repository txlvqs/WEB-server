#include "other.h"

void fileDoenload(char *message, int client_socket)
{
    printf("进入下载函数");
    char *mes;
    char buffer[1024] = "";
    char *text;//读取文件内容
    char *ptr;

    char pos[] = "HTTP/1.1 200 OK\r\n" // POST报头
                 "Content-Type: text/plain\r\n"
                 "Access-Control-Allow-Origin: *\r\n"
                 "content-Disposition: attachment;filename="test.txt"\r\n"
                 "Content-Lenth:10\r\n"
                 "atche-Control:public\r\n\r\n";

    char err[]="HTTP/1.1 404 NOT Found\r\n"//错误报头
    			"Content-Type:text/html\r\n\r\n"
			"<HTML><BODY>file not found</BODY></HTML>";

    // 处理聊天消息
    mes = strstr(message, "fileDoenload="); // 定位消息
    printf("mes=%s\n", mes + 13);
    printf("将处理发送的buf");
    memset(buffer, 0x00, sizeof(buffer)); // 清空传回buffer
    strcpy(buffer, mes + 13);             // 将聊天信息赋值到回传buffer中

    // 打开服务器中的文件
    printf("---------------------即将发送广播消息\n");

    if ((fd = open(buffer, O_RDONLY | O_BINARY)) < 0)
    {
        if (errno == ENOENT) // 如果打开失败
        {
            if (send(client_fd, err, strlen(err), 0) < 0) // 发送错误报头
            {
                perror("Error send 404\n");
            }
            close(fd);
            close(client_socket);
            return;
        }
    }

    //根据请求类型发送报头
    send(client_socket, pos, strlen(pos), MSG_DONTWAIT);

    // 发送文件内容

   /*发送请求内容*/
		while((bytes = read(fd,text,1024))>0)
		{
			if(send( client_socket,text,bytes,0)<0)//发送请求内容 
			{
			perror("Error send file but file ok\n");
			memset(text,0x00,sizeof(text));//清空传回内容 
			}
		} 
		printf("\n\n--------------------文件发送成功！----------------------\n\n");
	
		close(fd);

    return;
}
