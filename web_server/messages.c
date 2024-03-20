#include"other.h" 
#include <libwebsockets.h>


//审查消息类型
void messages(int client_socket,char *buffer)
{
	printf("进入消息处理函数");
	if(strstr(buffer, "message->back")!= NULL)//接收到退出聊天请求 
		{
			
  			 
		}
	else if(strstr(buffer, "message->login")!= NULL)//接收到登录聊天请求 
	{	
		
	}else 
		{
			printf("即将进入广播函数");
			message(buffer,client_socket);//传入广播室函数发送广播消息，仅加入消息列表的套接字可以接收到 
		}
		return;
}
	

//发送消息
void message(char *message,int client_socket){
	printf("成功进入广播函数\n");
	
	char *mes; 
	int arr[5]; 
	char buffer[1024]=""; 
	
	char pos[]="HTTP/1.1 200 OK\r\n"//POST报头
		   "Content-Type: text/plain\r\n"
		   "Access-Control-Allow-Origin: *\r\n"
		   "Content-Lenth:60\r\n"
		   "atche-Control:public\r\n\r\n";

	
	
		//处理聊天消息 
		mes=strstr(message,"message=");//定位消息 
		printf("mes=%s\n",mes+8);
		printf("将处理发送的buf");
		memset(buffer,0x00,sizeof(buffer));//清空传回buffer
		strcpy(buffer, mes+8);//将聊天信息赋值到回传buffer中 
		
		//发送
		printf("---------------------即将发送广播消息\n");
		printf("发送内容：%s\n",buffer);
		send(client_socket,pos,strlen(pos),MSG_DONTWAIT);
		send(client_socket,buffer,strlen(buffer),MSG_DONTWAIT);
		printf("发送成功\n");

    		//send(client_socket,buffer,strlen(buffer),0);//发内容 
	
	return;	 
}
