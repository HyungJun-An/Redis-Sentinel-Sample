#include <stdio.h>
#include <stdlib.h>
#include <hiredis.h>
#include <string.h>	
#include <signal.h>
/************************/
/*전역 변수 선언	*/
/************************/

redisContext *conn_slave=NULL;
redisContext *conn_slave_slave=NULL;
redisReply *resp =NULL;
int loop=0;
char sql[64];
char name[64];
/************************/
/*함수 선언		*/
/************************/
int init();
void (*sig) ( int);
/*************************************/
/*파라미터 잘못 입력시 출력 및 종료  */
/*************************************/
static void argc_text()
{
	fprintf(stderr, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
	fprintf(stderr, "[Usage]: redis-slave-2 \"name\"\n");
	fprintf(stderr, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
/********************************/
/*로그아웃 시그널 함수		*/
/********************************/
void sigint_handler( int signo)
{
	sprintf(sql,"SET %s logout",name);
	resp = (redisReply *)redisCommand(conn_slave,sql,1);
	printf("\nLogout %s %s\n",name,resp->str);
	exit(0);
	
}
/********************************/
/*name: redis-slave-2.c		*/
/*중복 로그인 확인		*/
/*20240411 anhj			*/
/********************************/
int main(int argc, char *argv[])
{
	/*****************************/
	/*파라미터 값 비정상일시 출력*/
	/*****************************/
	if(argc!=2)
	{
		argc_text();
		return 0;
	}
	/********************************/
	/*로그아웃 시 시그널 호출	*/
	/********************************/
	sig = signal( SIGINT,sigint_handler);
	/*************/
	/*변수 선언  */
	/*************/
	int rtn=0;
	char status[64];
	memset(name,0x00,sizeof(name));
	memset(status,0x00,sizeof(status));
	memcpy(name,argv[1],sizeof(argv[1]));
	/************/
	/*init redis*/
	/************/
	rtn=init();
	if(rtn!=1)
	{
		printf("init failed\n");
		return 0;
	}
	memset(sql,0x00,sizeof(sql));
	sprintf(sql,"GET %s",name);
	
	/********************/
	/*key value가져오기 */
	/********************/	
	resp = (redisReply *)redisCommand(conn_slave_slave,sql,1);
	if (NULL ==resp)
	{
		redisFree(conn_slave_slave);
		return 0;
	}

	if (REDIS_REPLY_ERROR == resp->type)
	{
		redisFree(conn_slave_slave);
		freeReplyObject(resp);
		return 0;
	}
	if(NULL==resp->str)
	{
		printf("%s의 해당하는 key가 존재하지않음\n",name);
		return 0;
	}
	strcpy(status,resp->str);
	freeReplyObject(resp);

	/************************/
	/*로그인 상태 확인	*/
	/************************/
	int logincheck=strcmp("logined",status);
	if(logincheck==0)
	{
		printf("이미 로그인 되어있습니다!\n");
		return 0;
	}
	/************************/
	/*로그인 상태로 변환	*/
	/************************/	
	sprintf(sql,"SET %s logined",name);
	resp = (redisReply *)redisCommand(conn_slave,sql,1);
	printf("Login %s %s\n",name,resp->str);
	if(NULL==resp)
	{
		redisFree(conn_slave);
		printf("SET command Error!");
		return 0;
	}
	while(1)
	{
	}
	/************/
	/*종료함수  */
	/************/
	redisFree(conn_slave);
	redisFree(conn_slave_slave);
}

int init()
{

	conn_slave_slave = redisConnect("127.0.0.1",6381);
	if ( (NULL!=conn_slave)&& conn_slave->err)
	{
		printf("error :%s\n",conn_slave->errstr);
		redisFree(conn_slave);
		return 0;
	}

	else if (NULL ==conn_slave)
	{
		return 0;
	}


	return 1;
}

