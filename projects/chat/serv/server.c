#include <sys/types.h>
#include <sys/socket.h>
#include <json-c/json.h>
#include <pthread.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "task.c"

#define PORT 3425
#define IP "127.0.0.1"
#define true 1

#define BUFFER_SZ 2048
#define NAME_LEN 32

#define MAX_CLIENTS 20
static _Atomic unsigned int cli_count=0;
static int uid=100;

//client struct
typedef struct{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[NAME_LEN];
	char recipientname[NAME_LEN];
}client_t;

client_t *clients[MAX_CLIENTS];

pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;

void str_overwrite_stdout(){
	printf("\r%s",">");
	fflush(stdout);
}
int is_task(const char * task){
	char * ptr;
	if(task[0=='-']){
		ptr=malloc(strlen(task)-1);
		for(int i=0;i<strlen(ptr);i++)
			ptr[i]=task[i+1];
	}else{
		ptr=malloc(strlen(task));
		for(int i=0;i<strlen(ptr);i++)
			ptr[i]=task[i];
	}
		if(strstr(ptr,"+")!= NULL || strstr(ptr,"-")!=NULL || strstr(ptr,"*")!=NULL || strstr(ptr,"/")!=NULL)
		return 1;

	return 0;
}
void str_trim_lf(char * arr,int len){
	for(int i=0;i<len;i++){
		if(arr[i]=='\n'){
			arr[i]='\0';
			break;
		}
	}
}

void in_err(int n,char * message){
	if(n<0){
		perror(message);
		exit(1);
	}
}
char * queue_get(char * name){
 //	pthread_mutex_lock(&client_mutex);
			for(int i=0;i<MAX_CLIENTS;i++){
				if(clients[i]!=NULL && clients[i]->recipientname!=NULL && strcmp(clients[i]->recipientname,name)==0){
					char * c_name=clients[i]->name;
					return c_name;
				}
			}
			return "false";
 //	pthread_mutex_unlock(&client_mutex);
}
void queue_add(client_t * cl){

	pthread_mutex_lock(&client_mutex);

	for(int i=0;i<MAX_CLIENTS;i++){
		if(clients[i]==NULL){
			clients[i]=cl;
			break;
		}
	}

	pthread_mutex_unlock(&client_mutex);
}

void queue_remove(int uid){

	pthread_mutex_lock(&client_mutex);

	for(int i=0;i<MAX_CLIENTS;i++){
		if(clients[i]!=NULL && clients[i]->uid==uid){
			clients[i]=NULL;
			break;
		}
	}
	pthread_mutex_unlock(&client_mutex);
}

void ptint_ip_addr(struct sockaddr_in addr){
	printf("%s",inet_ntoa(addr.sin_addr));

}

void send_message(char *s,client_t *cli){

	pthread_mutex_lock(&client_mutex);

	for(int i=0;i<MAX_CLIENTS;i++){
		if(clients[i]!=NULL && clients[i]->uid!=cli->uid && strcmp(clients[i]->name,cli->recipientname)==0 ){
			int send_res=send(clients[i]->sockfd,s,strlen(s),0);
			if(send_res<0){
				printf("Error :send!");
				break;
			}
		}
	}
	pthread_mutex_unlock(&client_mutex);

}

void * handle_client(void * arg){
	char buffer[BUFFER_SZ];
	char name[NAME_LEN];
	char recipientname[NAME_LEN];
	int leave_flag=0;
	cli_count++;

	client_t *cli = (client_t *)arg;

	if(recv(cli->sockfd,name,NAME_LEN,0)<=0 || strlen(name)>32){
		printf("Enter the name correctly\n");
		leave_flag=1;
	}else{
		strcpy(cli->name,name);
		printf("\n" );
		sprintf(buffer,"%s has joined\n",cli->name);
		printf("%s",buffer);
	//	send_message(buffer,cli);
	}

	bzero(name,NAME_LEN);
	bzero(buffer,BUFFER_SZ);

	char * gh=queue_get(cli->name);
	send(cli->sockfd,gh,strlen(gh),0);

		if(recv(cli->sockfd,recipientname,NAME_LEN,0)<=0 || strlen(recipientname)>32){
			printf("Enter the recipientname correctly\n");
			leave_flag=1;
		}else{
			strcpy(cli->recipientname,recipientname);
		}
			bzero(recipientname,NAME_LEN);
			bzero(buffer,BUFFER_SZ);
			char tasks[2048];

	while(true){
		if(leave_flag){
			break;
		}
		int receive=recv(cli->sockfd,buffer,BUFFER_SZ,0);

		struct json_object * parser_json=json_tokener_parse(buffer);
		struct json_object * jname;
		struct json_object *jmessage;
		struct json_object *jtask;
		struct json_object *jserv_sec;
		struct json_object *jcli_sec;
		struct json_object *jobj;

		if(strstr(buffer,"exit") !=NULL){

			jobj=json_object_new_object();
			jmessage=json_object_new_string("has left");

			json_object_object_get_ex(parser_json,"Name",&jname);

			json_object_object_add(jobj,"Name",jname);
			json_object_object_add(jobj,"Message",jmessage);

			bzero(buffer,BUFFER_SZ);
			const char * ptr=json_object_get_string(jname);
			printf("\n%s has left\n",ptr );
			sprintf(buffer,"%s\n",json_object_get_string(jobj));
			send_message(buffer,cli);
			leave_flag = 1;
		}else if(receive > 0){
			if(strlen(buffer)>0){
				json_object_object_get_ex(parser_json,"Message",&jmessage);
				const char * ptr=json_object_get_string(jmessage);

				if(is_task(ptr)==0){
					json_object_object_get_ex(parser_json,"ServerSec",&jserv_sec);
					json_object_object_get_ex(parser_json,"ClientSec",&jcli_sec);
					json_object_object_get_ex(parser_json,"Task",&jtask);

					const char * tas=json_object_get_string(jtask);

					int s_sec=json_object_get_int(jserv_sec);
					int c_sec=json_object_get_int(jcli_sec);

					//printf("c_sec: %d\n",c_sec);
				 //	printf("s_sec: %d\n",s_sec );

					if(c_sec-s_sec>19){
						char time_mess[1024];
						sprintf(time_mess,"Time is up! %s did not have time.",cli->name);
						jmessage=json_object_new_string(time_mess);
						jname=json_object_new_string("Server");
						jobj=json_object_new_object();

						json_object_object_add(jobj,"Name",jname);
						json_object_object_add(jobj,"Message",jmessage);

						sprintf(buffer,"%s\n",json_object_get_string(jobj));
						send_message(buffer,cli);
						continue;
					}

					int cli_res=json_object_get_int(jmessage);
					int res=stringConvertToArithmeticOperations(tas);


					if(res==cli_res){
						send_message(buffer,cli);
					}else{
						jmessage=json_object_new_string("Wrong resolt!");
						jname=json_object_new_string("Server");
						jobj=json_object_new_object();

						json_object_object_add(jobj,"Name",jname);
						json_object_object_add(jobj,"Message",jmessage);
						json_object_object_add(jobj,"ServerSec",jserv_sec);

						sprintf(buffer,"%s\n",json_object_get_string(jobj));
						send(cli->sockfd,buffer,sizeof(buffer),0);
					}
					//strcpy(tasks,ptr);
					//send_message(buffer,cli);
				}else{

					time_t currenttime;
					time(&currenttime);

					struct tm * mytime=localtime(&currenttime);
					jserv_sec=json_object_new_int(mytime->tm_hour*3600+mytime->tm_min*60+mytime->tm_sec);

					jobj=json_object_new_object();

					json_object_object_get_ex(parser_json,"Message",&jmessage);
					json_object_object_get_ex(parser_json,"Task",&jtask);
					json_object_object_get_ex(parser_json,"Name",&jname);

					json_object_object_add(jobj,"Name",jname);
					json_object_object_add(jobj,"Message",jmessage);
					json_object_object_add(jobj,"ServerSec",jserv_sec);

					const char * t_1=json_object_get_string(jobj);
					char  s_buffer[strlen(t_1)];
					for(int i=0;i<strlen(t_1);i++){
						s_buffer[i]=t_1[i];
					}
					send_message(s_buffer,cli);
				}
				str_trim_lf(buffer,strlen(buffer));
			}
		}else{
			printf("Error:-1\n");
			leave_flag = 1;
		}
		bzero(buffer,BUFFER_SZ);
	}
	close(cli->sockfd);
	queue_remove(cli->uid);
	free(cli);
	cli_count--;
	pthread_detach(pthread_self());

	return NULL;

}

int main(){

	int listenfd=0,connfd=0;
	struct sockaddr_in serv_addr;
	struct sockaddr_in cli_addr;
	pthread_t tid;

	//Socket Settings
	listenfd=socket(AF_INET,SOCK_STREAM,0);
	in_err(listenfd,"Error:socket!");

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(PORT);
	serv_addr.sin_addr.s_addr=inet_addr(IP);

	int bind_res;
	bind_res=bind(listenfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr));
	in_err(bind_res,"Error:bind! ");

	in_err(listen(listenfd,10),"Error:listen");

	printf("============ WELCOME =============\n");

	while(true){

	  int cli_size;
	  connfd=accept(listenfd,(struct sockaddr *)&cli_addr,&cli_size);
	  in_err(connfd,"Error:accept!");
	  if(cli_count+1==MAX_CLIENTS){

	      printf("Maximum clients connected.Connection Rejected\n");
	      ptint_ip_addr(cli_addr);
	      close(connfd);
	      continue;
	  }
	  //clients setings
	  client_t *cli=(client_t *)malloc(sizeof(client_t));
	  cli->address=cli_addr;
	  cli->sockfd=connfd;
	  cli->uid=uid++;

	  queue_add(cli);
	  pthread_create(&tid,NULL,&handle_client,(void *) cli);
	  sleep(1);
	}
	return EXIT_SUCCESS;
}
