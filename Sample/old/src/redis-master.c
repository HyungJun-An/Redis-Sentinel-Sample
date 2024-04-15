#include <stdio.h>
#include <stdlib.h>
#include <hiredis.h>
#include <string.h>	
#include <signal.h>
/************************/
/*전역 변수 선언	*/
/************************/

redisContext *conn=NULL;
redisReply *resp =NULL;
redisReply *master =NULL;
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
	fprintf(stderr, "[Usage]: redis-master \"name\"\n");
	fprintf(stderr, "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
}
/********************************/
/*로그아웃 시그널 함수		*/
/********************************/
void sigint_handler( int signo)
{
	sprintf(sql,"SET %s logout",name);
	resp = (redisReply *)redisCommand(conn,sql,1);
	printf("\nLogout %s %s\n",name,resp->str);
	exit(0);
	
}
/********************************/
/*name: redis-master.c		*/
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
		printf("connection failed");
		return 0;
	}
	memset(sql,0x00,sizeof(sql));
	sprintf(sql,"GET %s",name);
	
	/********************/
	/*key value가져오기 */
	/********************/	
	resp = (redisReply *)redisCommand(conn,sql,1);
	if (NULL ==resp)
	{
		redisFree(conn);
		return 0;
	}

	if (REDIS_REPLY_ERROR == resp->type)
	{
		redisFree(conn);
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
		redisFree(conn);
		return 0;
	}
	/************************/
	/*로그인 상태로 변환	*/
	/************************/	
	sprintf(sql,"SET %s logined",name);
	resp = (redisReply *)redisCommand(conn,sql,1);
	printf("Login %s %s\n",name,resp->str);
	if(NULL==resp)
	{
		redisFree(conn);
		printf("SET command Error!");
		return 0;
	}
	while(1)
	{
	}
	/************/
	/*종료함수  */
	/************/
	redisFree(conn);
}

int init()
{
	/********************************/
	/*redis-sentinel 접근		*/
	/*2024.04.15 anhj		*/
	/********************************/
	char MasterIP[16];
	memset(MasterIP,0x00,sizeof(MasterIP));
	conn = redisConnect("127.0.0.1",33059);//containerName[reids-redis-sentinel-1]
	if ( (NULL!=conn)&& conn->err)
	{
		printf("error :%s\n",conn->errstr);
		redisFree(conn);
		return 0;
	}

	resp=(redisReply *)redisCommand(conn,"SENTINEL MASTERS");
	if ( resp ==NULL || resp->type == REDIS_REPLY_ERROR)
	{
		printf("Error Failed to execute SENTINEL MASTERS\n");
		exit(EXIT_FAILURE);
	}
	
	/************************/
	/*현재 master ip가져오기*/
	/************************/
	if ( resp->type == REDIS_REPLY_ARRAY && resp->elements >0)
	{
		int i=0;
		while(i< resp->elements)
		{
			redisReply *master = resp->element[i];
			i++;
		}
		strcpy(MasterIP, master->element[3]->str);
		freeReplyObject(master);
		freeReplyObject(resp);
	}

	/******************/
	/*현재 master conn*/
	/******************/
	conn = redisConnect(MasterIP,6379);

	if ( (NULL!=conn)&& conn->err)
	{
		printf("error :%s\n",conn->errstr);
		redisFree(conn);
		return 0;
	}

	else if (NULL ==conn)
	{
		return 0;
	}

	return 1;
}

