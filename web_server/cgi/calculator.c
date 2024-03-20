#include <stdio.h>
#include <stdlib.h>
#include <string.h> 


#define MAX_SIZE 100


/*定义栈以及栈操作----*/ 
//定义栈主体 
typedef struct{
    int data[MAX_SIZE];
    int top;
}Stack;

// 初始化栈
void init(Stack *s) {
    s->top = -1;
}

// 判是否栈空
int is_empty(Stack *s) {
    return (s->top == -1);
}

// 判断是否栈满 
int is_full(Stack *s) {
    return (s->top == MAX_SIZE - 1);
}

// 入栈
void push(Stack *s, int value) {
    if (is_full(s)) {
        printf("栈溢出\n");
        exit(1);
    }
    s->data[++(s->top)] = value;
}

// 出栈
int pop(Stack *s) {
    if (is_empty(s)) {
        printf("栈下溢\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

// 获取栈顶元素
int peek(Stack *s) {
    if (is_empty(s)) {
        printf("栈为空\n");
        exit(1);
    }
    return s->data[s->top];
}


/*----定义栈以及栈操作*/



/*输入检测函数----*/


// 检测输入是否为数字
int isNumber(char c) {
    if(c >= '0' && c <= '9')
    {
    	return 1;
	}
	else return 0; 
	 
}


// 检测输入是否为运算符
int isOperator(char c) {
	
	
	static int Ope = 0; //静态变量，作运算符计数阀，当连续两次传入运算符时阀门报错 

	if(c == '+' || c == '-' || c == '*' || c == '/') 
	{
		Ope++;
		if(Ope<2)//运算符不可以连续两次调用运算符，超出返回0
		{
			return 1;//没有异常返回1	
		 }
		 else{
		 	return 0;
		 } 	
	}
	else{
		Ope = 0;//当检测非运算符时，重置计数阀
		
	}
     return 0; 
}


// 检测输入是否为括号
int isBrackets(char c) {
	
    	return (c == '(' || c == ')');
 
}


//检测括号是否匹配 
int matchBrackets(const char* input)
{	
	int q = 0;//检测括号是否匹配
	static int Br;//统计括号对数 
	Br = 0; 
	for(int i = 0; i < strlen(input); i++)//遍历字符串
	{
		if( input[i] == '(' )
		{
			q++;
			Br++;
			
		 } 
		 	
		if( input[i] == ')' )
		{
			q--;	
		}
		 	
	}
	//括号匹配并且统计出有几对括号时返回，返回值为括号对数
	if(q == 0 && Br > 0) 
	{
		return Br;
	 }
	 
	//有括号但括号不匹配时返回-1
	if(q != 0 && Br > 0) 
	{
		return -1;
	 }
	 
	//没有检测到括号返回0
	if(q == 0 && Br == 0)
	{
		return 0;
	} 

}



//开始检测 

int judge(const char* input){
//	printf("检测函数执行\n\n");

	int jug = 1;//判断变量，1为通过，0为未通过，下方进行多层检测，只要有一次异常将判定该变量为0立即返回异常 
	
	jug = ( !isOperator(input[0]) && !isOperator(input[strlen(input)-1])  );//1、首尾字符检测为运算符号立即判false 
	
	if(matchBrackets(input)<0) //2、检测括号不匹配立即判false
		jug = 0; 
 
	
    for (int i = 0; i < strlen(input); i++)//遍历字符串
	{	 
	 	if(jug == 0)
	 	{
//		 	printf("您的输入有误，请重新输入\n");
	 		return 0;//检测到0不合格立即返回 
		 }
		 //3、判断字符合法性 
		jug =isOperator(input[i])||isNumber(input[i])||isBrackets(input[i]);//三个检测字符函数至少一个返回值是1，如果均为0则未通过检测
		
	 }
	 
	 //测试
	 if(jug == 1)
	 {
	 	//printf("您的输入正确，程序继续执行\n"); 
	  } 
	 
	 	 
	return jug; //4、直到最终都是检测全部为1则通过检测，否则无论如何都返回0

}
/*----输入检测函数*/








/*运算函数----*/ 

// 定义运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    } else {
        return 0;
    }
}

// 计算函数
int apply_operator(int a, int b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
        	if(b == 0)
        	{
        		printf("检测被除数为0，程序终止\n");
				system("pause"); 
        		exit(0); 
			}
            return a / b;
        default:
            return 0;
    }
}


//计算器函数 
int calculate(const char *input) {
    Stack operand_stack;  // 数字栈
    Stack operator_stack; // 运算符栈
    init(&operand_stack);  // 初始化数字栈
    init(&operator_stack); // 初始化运算符栈
    
    //传入计算函数的临时容器 
    int b;//初始化数字容器 
    int a;//初始化数字容器
    char op;//初始化运算符容器

    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i]>='0'&&input[i]<='9') {  // 1、检测是数字
            int operand = 0;
            do { //将字符数字转为整型数字并将连续的单个数字合并一个为多位数字
				operand = operand * 10 + (input[i] - '0');
                i++;//遍历下标后移，离开循环时遍历下标已经指向非数字字符 
            }while (input[i]>='0'&&input[i]<='9'); //循环检测下一个是否依旧是数字，直到不是数字离开循环
            i--;
            push(&operand_stack, operand);  // 将数字压入数字栈
            
        } else if (input[i] == '(') {  // 2、括号检测：如果是左括号
        
            push(&operator_stack, input[i]);  // 将左括号压入运算符栈
        
		} else if (input[i] == ')') {  // 如果是右括号，开始提取右括号之前
            while (!is_empty(&operator_stack) && peek(&operator_stack) != '(') {//在配对到入栈的左括号前，将所有栈内数据弹出进行运算，优先小括号内计算 
            	
            	
            	a = pop(&operand_stack);//弹栈提取一个数字 
                b = pop(&operand_stack);//弹栈提取第二个数字
                op = pop(&operator_stack);//弹栈提取符号 
                
                
                push(&operand_stack, apply_operator(a, b, op));  // 从操作数栈和运算符栈中弹出操作数和运算符进行运算，并将结果压入数字栈
            }
            
            pop(&operator_stack);  // 丢弃 '('
        } else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {  // 如果是运算符
            while (!is_empty(&operator_stack) && precedence(peek(&operator_stack)) >= precedence(input[i])) {//当新符号优先级低于栈顶符号时，优先计算栈顶符号 
            	
            	a = pop(&operand_stack);//弹栈提取一个数字 
                b = pop(&operand_stack);//弹栈提取第二个数字
                op = pop(&operator_stack);//弹栈提取符号      
                
                push(&operand_stack, apply_operator(a, b, op));  // 从操作数栈和运算符栈中弹出操作数和运算符，进行运算，并将结果压入操作数栈
            }
            push(&operator_stack, input[i]);  // 当新符号优先级高于或等于栈顶运算符，则将新运算符压入运算符栈
        }
    }

    // 处理剩余的运算符和操作数
    while (!is_empty(&operator_stack)) {
    	
        a = pop(&operand_stack);//弹栈提取一个数字 
        b = pop(&operand_stack);//弹栈提取第二个数字
        op = pop(&operator_stack);//弹栈提取符号 
        
        push(&operand_stack, apply_operator(a, b, op));  // 从操作数栈和运算符栈中弹出操作数和运算符，进行运算，并将结果压入操作数栈
    }

    return pop(&operand_stack);  // 返回最终结果
}

/*----运算函数*/






int main() {
    char input[100];
    int result;
    while(1)
    {
    	printf("请输入需要计算的算式（不必写等于号，输入0退出程序）\n"); 
        scanf("%s",input); 
    if(strcmp(input,"0") == 0){
    	printf("程序退出\n"); 
		break;
	}
	else if(judge(input) == 0)
	{
	printf("您的输入有误，请检查后重新输入\n"); 
	}else
	{
	 result = calculate(input);
   	printf("结果: %d\n", result);	
	}
	}
    
    
    return 0;
}

