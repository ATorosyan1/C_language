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
#include <signal.h>
#include <time.h>

#define PORT 3425
#define IP "127.0.0.1"
#define true 1

#define BUFFER_SZ 2048
#define NAME_LEN_1 32
#define TASK_LEN 2048

volatile sig_atomic_t flag=0;
volatile sig_atomic_t last_message = 1;
int serv_time=-1;
int sockfd=0;
char name[NAME_LEN_1];
char recipientname[NAME_LEN_1];
char last_task[TASK_LEN];

void str_overwrite_stdout(){
	if(last_message==1){
		printf("\r%s","Enter the expression: ");
	}else if(last_message==0){
		printf("\r%s","Enter resolt: " );
		last_message = -1;
		goto p;
	}else{
		printf("\r%s",">" );
	}
	p:
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
int is_task(const char * task){
		if(strstr(task,"+")!= NULL || strstr(task,"-")!=NULL || strstr(task,"*")!=NULL || strstr(task,"/")!=NULL)
		return 1;

	return 0;
}
void in_err(int n,char * message){
	if(n<0){
		perror(message);
		exit(1);
	}
}
void catch_ctrl_c_and_exit(){
	flag=1;
}
void  send_msg_handler(){
	char buffer[BUFFER_SZ]={};
	while(true){
		str_overwrite_stdout();
		time_t currenttime;
		time(&currenttime);

		struct tm * mytime=localtime(&currenttime);
		//input buffer
		fgets(buffer,BUFFER_SZ,stdin);
		str_trim_lf(buffer,BUFFER_SZ);


		struct json_object * jobj=json_object_new_object();
		struct json_object *jmessage=json_object_new_string(buffer);
		struct json_object *jname=json_object_new_string(name);
		struct json_object *jtask=json_object_new_string(last_task);
		struct json_object *jserv_sec=json_object_new_int(serv_time);
		struct json_object *jclient_sec=json_object_new_int(mytime->tm_hour*3600+mytime->tm_min*60+mytime->tm_sec);

		json_object_object_add(jobj,"Name",jname);
		json_object_object_add(jobj,"Message",jmessage);

		int falg_1=0;
		if(strstr(json_object_get_string(jmessage),"Wrong resolt!")!=NULL){
			falg_1=1;
		}
		if(is_task(buffer)==0){
			json_object_object_add(jobj,"Task",jtask);
			json_object_object_add(jobj,"ServerSec",jserv_sec);
			json_object_object_add(jobj,"ClientSec",jclient_sec);
			if(falg_1==0){
				last_message=1;
			}
		}/*else{
			last_message=-1;
		}*/
		const char * message=json_object_to_json_string(jobj);
		send(sockfd,message,strlen(message),0);
	//serv_time = -1;
		if(strcmp(buffer,"exit")==0){
			bzero(buffer,BUFFER_SZ);
			break;
		}
		bzero(buffer,BUFFER_SZ);
	}
	catch_ctrl_c_and_exit();
}

void recv_msg_handler(){
	char message[BUFFER_SZ];
	char buffer[BUFFER_SZ];

	while(true){

		bzero(message,BUFFER_SZ);
		int receive=recv(sockfd,message,BUFFER_SZ,0);

		struct json_object * json_parser;
		struct json_object * jname;
		struct json_object * jmessage;
		struct json_object * jserv_time;

		if(receive>0){
			last_message =-1;
			json_parser=json_tokener_parse(message);
			json_object_object_get_ex(json_parser,"Name",&jname);
			json_object_object_get_ex(json_parser,"Message",&jmessage);

			int flag_2=0;
			int flag_3=0;
			if(is_task(json_object_get_string(jmessage))==1){
				flag_2=1;
				strcpy(last_task,json_object_get_string(jmessage));
				json_object_object_get_ex(json_parser,"ServerSec",&jserv_time);
				serv_time=json_object_get_int(jserv_time);
			}else{
				flag_3=1;
			}
			int flag_4=0;
			int t_h;
			if(strstr(json_object_get_string(jmessage),"Wrong resolt!")!=NULL){
				last_message=0;
				flag_4=1;

				time_t currenttime2;
				time(&currenttime2);

				struct tm * mytime_2=localtime(&currenttime2);
			 	t_h=mytime_2->tm_hour*3600+mytime_2->tm_min*60+mytime_2->tm_sec;

			}
			printf("\n\n");

			sprintf(buffer,"%s: %s ",json_object_get_string(jname),json_object_get_string(jmessage));

			printf("%s\n",buffer);

			if(flag_4==1){
				if(t_h-serv_time<=20){
					printf("Left: %d:%d:%d\n\n",0,0,20-(t_h-serv_time));
				}
			}

			if(flag_4==0){
				if(flag_2==1){
					last_message=0;
				}
				if(flag_3==1){
					last_message=1;
				}
			}
			str_overwrite_stdout();
		}else if(receive==0){
			break;
		}
		bzero(message,BUFFER_SZ);
	}
}
int main(int argc,char ** argv){

	printf("Enter your name: ");
	fgets(name,NAME_LEN_1,stdin);
	str_trim_lf(name,strlen(name));

	if(strlen(name)>NAME_LEN_1-1 || strlen(name)<2){
		printf("Enter name correctly\n");
		return EXIT_FAILURE;
	}

/*	printf("%s","To whom to send messages: " );
	fgets(recipientname,NAME_LEN_1_1,stdin);
	str_trim_lf(recipientname,strlen(recipientname));

	if(strlen(recipientname)>NAME_LEN_1-1 || strlen(recipientname)<2){
		printf("Enter recipientname correctly\n");
		return EXIT_FAILURE;
	}*/
	struct sockaddr_in server_addr;

	//Socket Settings
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	in_err(sockfd,"Error:socket!");

	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(PORT);
	server_addr.sin_addr.s_addr=inet_addr(IP);

	//connect to server
  int err=connect(sockfd,(struct sockaddr *)&server_addr,sizeof(server_addr));
	in_err(err,"Error : connect!");

	//send name
	char buf_2[100];
	send(sockfd,name,NAME_LEN_1,0);
	recv(sockfd,buf_2,100,0);
	//printf("res: %s\n",buf_2 );
	if(strcmp(buf_2,"false")!=0){

		send(sockfd,buf_2,strlen(buf_2),0);

	}else{
		printf("%s","To whom to send messages: " );
		fgets(recipientname,NAME_LEN_1,stdin);
		str_trim_lf(recipientname,strlen(recipientname));

		if(strlen(recipientname)>NAME_LEN_1-1 || strlen(recipientname)<2){
			printf("Enter recipientname correctly\n");
			return EXIT_FAILURE;
		}
		send(sockfd,recipientname,NAME_LEN_1,0);
		//str_trim_lf(recipientname,strlen(recipientname));
	}
		//send(sockfd,recipientname,NAME_LEN_1,0);
		bzero(buf_2,strlen(buf_2));
	printf("============ WELCOME =============\n");


	pthread_t send_msg_thread;
	pthread_t recv_msg_thread;

        if(pthread_create(&send_msg_thread,NULL,(void*)send_msg_handler,NULL) != 0)
	{
		printf("Error:thread craete!");
		return EXIT_FAILURE;

	}

        if(pthread_create(&recv_msg_thread,NULL,(void*)recv_msg_handler,NULL) != 0)
	 {
		printf("Error:thread craete!");
		return EXIT_FAILURE;

	 }
	while(1){
		if(flag){
			printf("\nbye\n");
			break;
		}
	}
	close(sockfd);
	return EXIT_FAILURE;


}
