#include <sys/types.h>
#include <sys/socket.h>
#include <json-c/json.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "task.c"

#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1

char *client_message;
void exit_func(void * arg){
	free(arg);
	printf("Exit!\n");
}
void * socketThread(void *arg){
	
	struct json_object * parsed_json;
	struct json_object * message;
	struct json_object * task;
	client_message=malloc(1024);

	//prohibits early termination of a thread
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	
	//sets the thread completion handler
	pthread_cleanup_push(exit_func,client_message);
	int newSocket = *((int *)arg);
	int recv_res=recv(newSocket,client_message,1024,0);	
	in_err(recv_res,"Error in recv method!");	
	
	parsed_json=json_tokener_parse(client_message);
	json_object_object_get_ex(parsed_json,"Message",&message);
	json_object_object_get_ex(parsed_json,"Task",&task);
	
	printf("Client message:%s\n",json_object_get_string(message));
	printf("\n");
	const char  *tas;;
	tas=json_object_get_string(task);
	char  str[strlen(tas)];
	for(int i=0;i<strlen(tas);i++){
		str[i]=tas[i];
		str[i+1]='\0';
	}

	int resoult=stringConvertToArithmeticOperations(str);
	struct json_object * jobj=json_object_new_object();
	struct json_object * jstring=json_object_new_string("Hello client!");
	struct json_object * jint=json_object_new_int(resoult);

	json_object_object_add(jobj,"Message",jstring);
	json_object_object_add(jobj,"Resoult",jint);

	const char * thhh=json_object_to_json_string (jobj);

	int send_res=send(newSocket,thhh,1024,0);
	in_err(send_res,"Error in send method!");
	close(newSocket);

	//permits early termination of a thread
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	
	//creates a thread cancel point.
	//pthread_testcancel();
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);

	//retrieves a thread completion handler
	pthread_cleanup_pop(NULL);
}

int main(){

	int mainsocket,newsocket,bind_res;
	struct sockaddr_in addr;
	struct sockaddr_storage serverStorage;
  	socklen_t addr_size;

	mainsocket=socket(AF_INET,SOCK_STREAM,0);
	in_err(mainsocket,"Error in socket method!");

	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=inet_addr(ADDRESS);

	bind_res=bind(mainsocket,(struct sockaddr *) &addr,sizeof(addr));
	in_err(bind_res,"Error in bind method!");
	
	in_err(listen(mainsocket,1),"Error in listen method!");
	
	while(true){
		
		pthread_t thread;
		addr_size = sizeof(serverStorage);
		newsocket = accept(mainsocket,(struct sockaddr *) &serverStorage,&addr_size);
		in_err(newsocket,"Error in accept method!");

		if( pthread_create(&thread, NULL, socketThread, &newsocket) != 0 )
          	printf("Failed to create thread\n");
		pthread_detach(thread);
		pthread_cancel(thread);
		
	}
	close(mainsocket);
	return 0;
	
}
