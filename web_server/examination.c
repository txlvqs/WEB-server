#include"other.h" 

void examination(char *message,int client_socket)
{
printf("进入考试函数");
	char *mes; 
	char buffer[1024]=""; 
	int value;
    int score =0;
	char *ptr;


	char pos[]="HTTP/1.1 200 OK\r\n"//POST报头
		   "Content-Type: text/plain\r\n"
		   "Access-Control-Allow-Origin: *\r\n"
		   "Content-Lenth:60\r\n"
		   "atche-Control:public\r\n\r\n";

		   
	
		//处理聊天消息 
		mes=strstr(message,"examination=");//定位消息 
		printf("mes=%s\n",mes+12);
		printf("将处理发送的buf");
		memset(buffer,0x00,sizeof(buffer));//清空传回buffer
		strcpy(buffer, mes+12);//将聊天信息赋值到回传buffer中 
		
		//发送
		printf("---------------------即将发送广播消息\n");
		
		score =0;

		ptr = strstr(buffer, "q1="); // 查找q1的位置
    if (ptr != NULL) {
        sscanf(ptr, "q1=%d", &value); // 提取q1的值
        printf("q1=%d\n", value);
		if(value == 5)
		{
			 score++;
		}
            
    }

    ptr = strstr(buffer, "q2="); // 查找q2的位置
    if (ptr != NULL) {
        
        sscanf(ptr, "q2=%d", &value); // 提取q2的值
        printf("q2=%d\n", value);
		if(value == 3)
		{
			score++;
		}
    }

    ptr = strstr(buffer, "q3="); // 查找q3的位置
    if (ptr != NULL) {
        sscanf(ptr, "q3=%d", &value); // 提取q3的值
        printf("q3=%d\n", value);
		 if(value == 10)
		 {
			score++;
		 }
    }

    ptr = strstr(buffer, "q4="); // 查找q4的位置
    if (ptr != NULL) {
        sscanf(ptr, "q4=%d", &value); // 提取q4的值
        printf("q4=%d\n", value);
		if(value == 6)
		{
			score++;
		}
        
    }

    ptr = strstr(buffer, "q5="); // 查找q5的位置
    if (ptr != NULL) {
        int value;
        sscanf(ptr, "q5=%d", &value); // 提取q5的值
        printf("q5=%d\n", value);
		if(value == 15)
		{
			score++;
		}
        
    }

        score*=20;
		printf("value=%d", value);
        sprintf(buffer, "%d", score);

		send(client_socket,pos,strlen(pos),MSG_DONTWAIT);
		send(client_socket,buffer,strlen(buffer),MSG_DONTWAIT);
		printf("发送成功\n");

    		//send(client_socket,buffer,strlen(buffer),0);//发内容 
	
	return;	
}
	