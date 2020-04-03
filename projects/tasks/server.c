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
#include "task.c"
#include <pthread.h>

#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1
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
	
	pthread_t tid[30];
    	int i = 0;
	while(true){
		
		addr_size=sizeof(serverStorage);
		newsocket=accept(mainsocket,(struct sockaddr *) &serverStorage, &addr_size);
		in_err(newsocket,"Error in accept method!");

			
		if( pthread_create(&tid[i], NULL, socketThread, &newsocket) != 0 )
          	printf("Failed to create thread\n");
		if( i >= 20)
     		   {
        		  i = 0;
         		  while(i < 20)
      			    {
        			    pthread_join(tid[i++],NULL);
        	            }
         			 i = 0;
      		    }
	}
	close(mainsocket);
	return 0;
	
}
