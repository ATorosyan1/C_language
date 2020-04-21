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
#define IP "127.0.0.90"
#define true 1

#define BUFFER_SZ 2048
#define NAME_LEN 32

volatile sig_atomic_t flag=0;
int sockfd=0;
char name[NAME_LEN];
char recipientname[NAME_LEN];

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
void catch_ctrl_c_and_exit(){
	flag=1;
}
void  send_msg_handler(){
	char buffer[BUFFER_SZ]={};
	char message[BUFFER_SZ+NAME_LEN]={};
	while(true){
		str_overwrite_stdout();

		//input buffer
		fgets(buffer,BUFFER_SZ,stdin);
		str_trim_lf(buffer,BUFFER_SZ);

		if(strcmp(buffer,"exit")==0){
			bzero(buffer,BUFFER_SZ);
			bzero(message,BUFFER_SZ+NAME_LEN);
			break;
		}else{
			sprintf(message,"%s: %s\n",name,buffer);
			send(sockfd,message,strlen(message),0);
		}
		bzero(buffer,BUFFER_SZ);
		bzero(message,BUFFER_SZ+NAME_LEN);
	}
	catch_ctrl_c_and_exit();
}

void recv_msg_handler(){
	char message[BUFFER_SZ];
	while(true){

		bzero(message,BUFFER_SZ);
		int receive=recv(sockfd,message,BUFFER_SZ,0);
		if(receive>0){
			printf("%s",message);
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
