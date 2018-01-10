/*******************************************************
 *功能：消息队列发送子程序；
 *
 *日期：Sep 23th. 2010
 *作者：Ropen Yuan
 *版本：V1.0
 * *****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PATHNAME  "tmp"            //文件可以任意打定，必须要指定对其路径
#define PROJID     12              //指定ftok函数的参数id

typedef struct student             //定义一个学生的成绩的结构体；
{
    char name[20];
    float score;
	char hope[20];
}STUD;

typedef struct msgbuf              //定义一个消息结构由两种方式来限定，第一，必须小于系统限制，第二必须以long 
{                                  //int 开始，这在接收函数中会用作一个消息类型；
    long int mtype;
    STUD student;
}BUFS;

int main(void)
{
    //消息队列：第一步建立一个相对惟一的key值

    key_t key=ftok(PATHNAME, PROJID);   //获得获得项目相关的IPC键值；合成一个相对惟一的key; 
    if(key==-1)                         //检测ftok函数的返回值，函数执行成功返回合成的key，失败返回-1;
    {
        perror("in msgsnd ,ftok");
        exit(-1);
    }

    //第二步：创建或打开消息队列
    
    int msgid = msgget(key, IPC_CREAT | 0600);   //创建或打开消息队列
    if(msgid == -1)                              //函数成功执行返回新生成的消息队列的描述符，失败返回-1;
    {
        perror("in msgsnd, msgget");
        exit(-1);
    }

    //第三步，向消息队列中写入数据
    BUFS buf;            //定义一个消息队列结构体；并且给消息队列元素赋值；
    buf.mtype = 8;
    buf.student.score = 90.9;
    strcpy(buf.student.name, "zhangsan");
	strcpy(buf.student.hope, "想发财");
while(1) {
    int ret = msgsnd(msgid,&buf,sizeof(buf)-sizeof(long),0); //成功返回0,失败返回1；
    if(ret == -1)
    {
        perror("in msgsnd, msgsnd");
        exit(-1);
    }
sleep(5);
}
    return 0;
}
