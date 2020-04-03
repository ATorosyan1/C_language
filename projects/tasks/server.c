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
<<<<<<< HEAD
#include "task.c"
#include <pthread.h>
=======
//#include "task.c"
>>>>>>> 190363d38868941c8aa13c8c9a91a08a6f8ea8fc

#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1
<<<<<<< HEAD
=======
void in_err(int n,char * message){
	if(n<0){
		perror(message);
		exit(1);
	}
}
int stringConvertToArithmeticOperations(char * buf){
	
	int length=0;
	while(buf[length]!='\0'){
		length++;
	}
	for(int i=0;i<length;i++){
		if(buf[i]>='A' && buf[i]<='z'){
			perror("Invalid String!");
			exit(1);
		}
	}
	char simvols[length];
	int numbers[length];
>>>>>>> 190363d38868941c8aa13c8c9a91a08a6f8ea8fc

char client_message[1024];
void * socketThread(void *arg){
	int newSocket = *((int *)arg);
	int recv_res=recv(newSocket,client_message,1024,0);	
	in_err(recv_res,"Error in recv method!");	
	int resoult=stringConvertToArithmeticOperations(client_message);
	itoa(resoult,client_message);
	//sleep(1);
	int send_res=send(newSocket,client_message,1024,0);
	in_err(send_res,"Error in send method!");
	close(newSocket);
	pthread_exit(NULL);
}
<<<<<<< HEAD
=======
 void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }
void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  
         n = -n;          
     i = 0;
     do {       
         s[i++] = n % 10 + '0';   
     } while ((n /= 10) > 0);   
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
>>>>>>> 190363d38868941c8aa13c8c9a91a08a6f8ea8fc
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
