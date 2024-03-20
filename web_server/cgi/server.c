#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/msg.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
char err_404[]="HTTP/1.1 404 NOT FOUND\r\n";

char status[]="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";//这行改
int main()
{
	int val = 1;
	signal(SIGPIPE,SIG_IGN);
	int qid = msgget(0x12345,IPC_CREAT|0666);
	int fd = socket(AF_INET,SOCK_STREAM,0);
	setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val));

	struct sockaddr_in info;
	info.sin_family = AF_INET;
	info.sin_port = htons(8696);
	info.sin_addr.s_addr = 0;

	bind(fd,(void*)&info,sizeof(info));
	listen(fd,10);
	char buf[1024];
	int newfd;
	while(1)
	{
		printf("999999\n");
		newfd = accept(fd,NULL,NULL);
		//	char buf[20];
		memset(buf,0x00,sizeof(buf));
		read(newfd,buf,sizeof(buf)-1);
		printf("%s",buf);
		int  fp = open("index.html",O_RDWR);
		memset(buf,0x00,sizeof(buf));
		read(fp,buf,sizeof(buf));
		puts(buf);
		write(newfd,status,sizeof(status)-1);//这行添
		write(newfd,buf,sizeof(buf)-1);
		close(fp);
		close(newfd);
	}
}
