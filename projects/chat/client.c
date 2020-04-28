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

#define BUffER_SZ 2048
#define NAME_LEN 32
#define TASK_LEN 2048

volatile sig_atomic_t flag=0;
volatile sig_atomic_t last_message = 1;
int serv_time=-1;
int sockfd=0;
char name[NAME_LEN];
char recipientname[NAME_LEN];
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
	char buffer[BUffER_SZ]={};
	while(true){
		str_overwrite_stdout();
		time_t currenttime;
		time(&currenttime);

		struct tm * mytime=localtime(&currenttime);
		//input buffer
		fgets(buffer,BUffER_SZ,stdin);
		str_trim_lf(buffer,BUffER_SZ);


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
	//	serv_time = -1;
		if(strcmp(buffer,"exit")==0){
			bzero(buffer,BUffER_SZ);
			break;
		}
		bzero(buffer,BUffER_SZ);
	}
	catch_ctrl_c_and_exit();
}

void recv_msg_handler(){
	char message[BUffER_SZ];
	char buffer[BUffER_SZ];

	while(true){

		bzero(message,BUffER_SZ);
		int receive=recv(sockfd,message,BUffER_SZ,0);

		struct json_object * json_parser;
		struct json_object * jname;
		struct json_object *jmessage;
		struct json_object *jserv_time;

		if(receive>0){
			last_message=-1;
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
			if(strstr(json_object_get_string(jmessage),"Wrong resolt!")!=NULL){
				last_message=0;
				flag_4=1;
			}
			printf("\n\n");

			sprintf(buffer,"%s: %s\n ",json_object_get_string(jname),json_object_get_string(jmessage));
			printf("%s\n",buffer);

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
		bzero(message,BUffER_SZ);
	}
}
int main(int argc,char ** argv){

	printf("Enter your name: ");
	fgets(name,NAME_LEN,stdin);
	str_trim_lf(name,strlen(name));

	if(strlen(name)>NAME_LEN-1 || strlen(name)<2){
		printf("Enter name correctly\n");
		return EXIT_FAILURE;
	}

	printf("%s","To whom to send messages: " );
	fgets(recipientname,NAME_LEN,stdin);
	str_trim_lf(recipientname,strlen(recipientname));

	if(strlen(recipientname)>NAME_LEN-1 || strlen(recipientname)<2){
		printf("Enter recipientname correctly\n");
		return EXIT_FAILURE;
	}
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
	send(sockfd,name,NAME_LEN,0);
	send(sockfd,recipientname,NAME_LEN,0);
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
