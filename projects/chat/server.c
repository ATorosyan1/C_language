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

#define PORT 3425
#define IP "127.0.0.26"
#define true 1

#define MAX_CLIENTS 3
#define BUFFER_SZ 2048
#define NAME_LEN 32

static _Atomic unsigned int cli_count=0;
static int uid=100;

//client struct
typedef struct{
	struct sockaddr_in address;
	int sockfd;
	int uid;
	char name[NAME_LEN];
}client_t;

client_t *clients[MAX_CLIENTS];

pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;

void str_overwrite_stdout(){
	printf("\r%s",">");
	fflush(stdout);
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

void send_message(char *s,int uid){
	
	pthread_mutex_lock(&client_mutex);
	
	for(int i=0;i<MAX_CLIENTS;i++){
		if(clients[i]!=NULL && clients[i]->uid!=uid){
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
	int leave_flag=0;
	cli_count++;

	client_t *cli = (client_t *)arg;
	
	if(recv(cli->sockfd,name,NAME_LEN,0)<=0 || strlen(name)>32){
		printf("Enter the name correctly\n");
		leave_flag=1;
	}else{
		strcpy(cli->name,name);
		sprintf(buffer,"%s has joined\n",cli->name);
		printf("%s",buffer);
		send_message(buffer,cli->uid);
	}

	bzero(buffer,BUFFER_SZ);

	while(true){
		if(leave_flag){
			break;
		}
		int receive=recv(cli->sockfd,buffer,BUFFER_SZ,0);
		if(receive>0){
			if(strlen(buffer)>0){
				send_message(buffer,cli->uid);
				str_trim_lf(buffer,strlen(buffer));
				printf("%s -> %s",buffer,cli->name);
			}
		}else if(receive == 0 || strcmp(buffer,"exit") == 0){
			sprintf(buffer,"%s has left \n",cli->name);
			printf("\n%s",buffer);
			send_message(buffer,cli->uid);
			leave_flag = 1;
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

	printf("===WELCOME TO THE CHATROOM===\n");

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









