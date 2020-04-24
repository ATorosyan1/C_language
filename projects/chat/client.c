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

#define PORT 3425
#define IP "127.1.0.2"
#define true 1

#define BUFFER_SZ 2048
#define NAME_LEN 32
#define TASK_LEN 2048

volatile sig_atomic_t flag=0;
int sockfd=0;
char name[NAME_LEN];
char recipientname[NAME_LEN];
char last_task[TASK_LEN];

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
	char buffer[BUFFER_SZ]={};
	while(true){
		str_overwrite_stdout();

		//input buffer
		fgets(buffer,BUFFER_SZ,stdin);
		str_trim_lf(buffer,BUFFER_SZ);

		struct json_object * jobj=json_object_new_object();
		struct json_object *jmessage=json_object_new_string(buffer);
		struct json_object *jname=json_object_new_string(name);
		struct json_object *jtask=json_object_new_string(last_task);

		json_object_object_add(jobj,"Name",jname);
		json_object_object_add(jobj,"Message",jmessage);

		if(is_task(buffer)==0){
			json_object_object_add(jobj,"Task",jtask);
		}
		const char * message=json_object_to_json_string(jobj);
		send(sockfd,message,strlen(message),0);

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
		struct json_object *jmessage;

		if(receive>0){
			json_parser=json_tokener_parse(message);
			json_object_object_get_ex(json_parser,"Name",&jname);
			json_object_object_get_ex(json_parser,"Message",&jmessage);

			if(is_task(json_object_get_string(jmessage))==1){
				strcpy(last_task,json_object_get_string(jmessage));
			}
			sprintf(buffer,"%s: %s\n ",json_object_get_string(jname),json_object_get_string(jmessage));
			printf("%s",buffer);
			str_overwrite_stdout();
		}else if(receive==0){
			break;
		}
		bzero(message,BUFFER_SZ);
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
	printf("===WELCOME TO THE CHATROOM===\n");


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
