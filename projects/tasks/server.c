#include <sys/types.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "task.c"
#include <pthread.h>

#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1

char *client_message;
void exit_func(void * arg){
	free(arg);
	printf("Exit!\n");
}
void * socketThread(void *arg){
	
	client_message=malloc(1024);

	//prohibits early termination of a thread
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	
	//sets the thread completion handler
	pthread_cleanup_push(exit_func,client_message);

	int newSocket = *((int *)arg);
	int recv_res=recv(newSocket,client_message,1024,0);	
	in_err(recv_res,"Error in recv method!");	
	int resoult=stringConvertToArithmeticOperations(client_message);
	itoa(resoult,client_message);
	int send_res=send(newSocket,client_message,1024,0);
	in_err(send_res,"Error in send method!");
	close(newSocket);

	//permits early termination of a thread
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	
	//creates a thread cancel point.
	pthread_testcancel();

	//retrieves a thread completion handler
	pthread_cleanup_pop(1);
	
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
		newsocket = accept(mainsocket,(struct sockaddr *) &serverStorage, &addr_size);
		in_err(newsocket,"Error in accept method!");

			
		if( pthread_create(&thread, NULL, socketThread, &newsocket) != 0 )
          	printf("Failed to create thread\n");
		pthread_cancel(thread);
		pthread_join(thread,NULL);
	}
	close(mainsocket);
	return 0;
	
}
