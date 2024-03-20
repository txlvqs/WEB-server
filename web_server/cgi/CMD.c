#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main() {
    char command[100];
    int result;
    printf("简单终端\n");
    
    while(1) {
        printf("$ ");
        fgets(command, sizeof(command), stdin);
        if (command[0] == 'c' && command[1] == 'd') {
            char* path = command + 3; // 获取cd命令后的路径
 		command[strcspn(command, "\n")] = 0;// 去除接收路径的\n，避免chdir函数读取路径附带额外的/n
            if (chdir(path) == -1) {// 改变工作目录
       		 perror("路径异常");
          	 }
        } else {
            result = system(command);
	if (result != 0) {
        printf("命令执行失败\n");
    }
        }
    }
    
    return 0;
}

