#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1

void in_err(int n,char * message){
	if(n<0){
		perror(message);
		exit(1);
	}
}

int main(){

	int mainsocket,connect_res,send_res,recv_res;
	char  string[1024];
	struct sockaddr_in addr;

	mainsocket=socket(AF_INET,SOCK_STREAM,0);
	in_err(mainsocket,"Error in socket method!");

	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=inet_addr(ADDRESS);

	connect_res=connect(mainsocket,(struct sockaddr *) &addr,sizeof(addr));
	in_err(connect_res,"Error in connect method!");
	
	while(true){
		printf("Enter String:\n");
		scanf("%s",string);
		
		int send_res=send(mainsocket,string,1024,0);
		in_err(send_res,"Error in send method!");
	
		recv_res=recv(mainsocket,string,1024,0);	
		in_err(recv_res,"Error in recv method!");
		printf("Resoult:%s\n",string);
		break;			
		
	}
	close(mainsocket);
	return 0;


	
}
