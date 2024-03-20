#include <stdio.h>
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
    int client_fd;//服务器套接字 
    struct sockaddr_in client_addr;
    int client_addr_len = sizeof(client_addr);
    
    char buffer[1024] ="";//接收报头 
    char filename[128]="";//提取文件名 
    char text[1024]="";//回发内容 
    // 处理请求
	char response[1024];

    int fd;//文件描述符
    ssize_t bytes;//字节数 

    char head[]="HTTP/1.1 200 OK\r\n"//网页报头
    			"Content-Type:text/html\r\n"
    			"\r\n";
    char png[]="HTTP/1.1 200 OK\r\n"//图片报头
    			"Content-Type:image/png\r\n"
    			"\r\n";
    char msc[]="HTTP/1.1 200 OK\r\n"//音乐报头
    			"Content-Type:audio/mpeg\r\n"
    			"\r\n";		
    char err[]="HTTP/1.1 404 NOT Found\r\n"//错误报头
    			"Content-Type:text/html\r\n"
			"\r\n"
			"<HTML><BODY>file not found</BODY></HTML>";

	
	


//开始连接 
    while (1) {
	printf("--------------在循环中等待下次连接---------------"); 
    	//建立连接	 
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, (socklen_t*)&client_addr_len);
        if (client_fd < 0) {
            perror("连接建立失败\n");
            exit(EXIT_FAILURE);
        }else
		printf("链接成功\n");

printf("VVVVVVVVVVVVVVVVVVVVVVVVVVVVV\n");
	
        // 读取请求
		memset(buffer,0x00,sizeof(buffer));
        read(client_fd, buffer, 1024);
        printf("buf值: %s\n", buffer);
        printf("读取请求成功\n");
        
printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");		

 /*访问根据报头需求查找文件 */
//处理GET请求
if  (strstr(buffer, "GET")!= NULL)
	{
		printf("进入查找函数"); 
		
		
		//识别报头，提取所需文件名 
		sscanf(buffer,"GET /%s",filename);
		printf("filename=%s\n",filename); 

		//提取文件名为空，则为访问主页
		if(strcmp(filename,"HTTP/1.1") == 0)
		{
			if((fd = open("index.html",O_RDONLY))< 0)
			{
				if(errno == ENOENT)//如果打开失败 
				{
					if(send(client_fd,err,strlen(err),0)<0)//发送错误报头 
					{
					perror("请求文件不存在，错误报头未发送\n");
					 }
 					close(fd);
					close(client_fd);
					break;
					printf("文件不存在，发送错误报头");
				}
			}	
		}
		//文件名非空，打开对应文件
		else if((fd = open(filename,O_RDONLY))<0) 
		{
			if(errno == ENOENT)//如果打开失败 
			{
				if(send(client_fd,err,strlen(err),0)<0)//发送错误报头 
				{
					perror("请求文件不存在，错误报头未发送\n");
				 } 
				close(fd);
				close(client_fd);
				break;
				
			}
		}

		printf("打开文件\n");

	/*发送报头*/
	if(strstr(filename, "html")!= NULL||strstr(filename, "HTTP")!= NULL)//网页和超链接请求发送网页报头
	{
		printf("发送超链接报头");
		if(send(client_fd,head,strlen(head),0)<0)
		{
		 	perror("head报头发送异常"); 
		}
		
	}else if(strstr(filename, "png")!= NULL) 
	{
		if(send(client_fd,png,strlen(png),0)<0)//图片请求发送图片报头
			{
			 	perror("png报头发送异常"); 
			}
	}else if(strstr(filename, "mp3")!= NULL)
	{
		if(send(client_fd,msc,strlen(msc),0)<0)//音乐请求发送音乐报头
			{
			 	perror("msc报头发送异常"); 
			}
	}
	

		printf("发送报头\n");


		/*发送请求内容*/
		while((bytes = read(fd,text,1024))>0)
		{
			if(send(client_fd,text,bytes,0)<0)//发送请求内容 
			{
			perror("请求文件存在，文件发送失败\n");
			memset(text,0x00,sizeof(text));//清空传回内容 
			}
		} 
		printf("\n\n--------------------文件发送成功！----------------------\n\n");
	
		close(fd);
		close(client_fd);
	
	}
	
	
}
	
	//处理POST请求 
	if (strstr(buffer, "POST") != NULL) {
	sprintf(response, );
	
	printf("输出post\n");
	} 	
	
	
        // 发送响应
	printf("%s\n",response);
       if(send(client_fd, response, strlen(response), 0) == -1)
	{
	    perror("发送失败\n");
        
	}

       printf("Response sent.\n");

        // 关闭连接
        close(client_fd);
    }
	close(server_fd);

    return 0;
}

