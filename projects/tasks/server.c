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
//#include "task.c"

#define PORT 8888
#define ADDRESS "127.0.0.3"
#define MAX_CLIENT 30
#define true 1
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

	int length_sim=0,length_num=0;
	int i=0;
	int resoult=0;
	while(i<length){
		if(buf[i]>='0' && buf[i]<='9'){
			int number=0;
			while(i<length && buf[i]>='0' && buf[i]<='9'){
					char sim[1];
					sim[0]=buf[i];
					number=number*10+atoi(sim);
					i++;
			}
			numbers[length_num++]=number;		
		} else if(buf[i]=='('){
			char str[length];
			int j=0,count_op=1,count_cl=0;;
			i++;
			while(count_op!=count_cl){
				str[j]=buf[i];
				if(buf[i]=='(')
					count_op++;
				if(buf[i]==')')
					count_cl++;
				i++;
				j++;
			}	
			str[j-1]='\0';
			numbers[length_num++]=stringConvertToArithmeticOperations(str);
		}else{
			simvols[length_sim++]=buf[i++];
		}
		
	}
	int t=1;
	while(t==1){
		int b=0;
		for(int k=0;k<length_sim;k++){
			if(simvols[k]=='*' || simvols[k]=='/'){
				if(simvols[k]=='*'){
					numbers[k]=numbers[k]*numbers[k+1];
				}
				if(simvols[k]=='/'){
					numbers[k]=numbers[k]/numbers[k+1];
				}
				for(int j=k+1;j<length_num-1;j++)
					numbers[j]=numbers[j+1];
				length_num--;
				for(int j=k;j<length_sim-1;j++)
					simvols[j]=simvols[j+1];

				length_sim--;
				b=1;
				break;
			}
		}
		t=b;
	}
	t=1;
	while(t==1){
		int b=0;
		for(int k=0;k<length_sim;k++){
			if(simvols[k]=='+' || simvols[k]=='-'){
				if(simvols[k]=='+'){
					numbers[k]=numbers[k]+numbers[k+1];
				}
				if(simvols[k]=='-'){
					numbers[k]=numbers[k]-numbers[k+1];
				}
				for(int j=k+1;j<length_num-1;j++)
					numbers[j]=numbers[j+1];
				length_num--;
				for(int j=k;j<length_sim-1;j++)
					simvols[j]=simvols[j+1];
				length_sim--;
				b=1;
				break;
			}
		}
		t=b;
	}
	resoult=numbers[0];
	return resoult;
	
	
}
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
int main(){

	int mainsocket,newsocket,bind_res,accept_res,send_res,recv_res;
	int sd,max_sd=-1,client_socket[MAX_CLIENT],activity;
	char  string[1024];
	fd_set readfds;	
	struct sockaddr_in addr;

	for(int i=0;i<MAX_CLIENT;i++){
		client_socket[i]=0;	
	}

	mainsocket=socket(AF_INET,SOCK_STREAM,0);
	in_err(mainsocket,"Error in socket method!");
	fcntl(mainsocket, F_SETFL, O_NONBLOCK);

	addr.sin_family=AF_INET;
	addr.sin_port=htons(PORT);
	addr.sin_addr.s_addr=inet_addr(ADDRESS);

	bind_res=bind(mainsocket,(struct sockaddr *) &addr,sizeof(addr));
	in_err(bind_res,"Error in bind method!");
	
	in_err(listen(mainsocket,1),"Error in listen method!");
	
	while(true){
		FD_ZERO(&readfds);
		FD_SET(mainsocket,&readfds);
		struct timeval timeout;
       		timeout.tv_sec = 2;
       	        timeout.tv_usec = 0;
		max_sd=mainsocket;

		for(int i=0;i<MAX_CLIENT;i++){
			sd=client_socket[i];
			if(sd!=0)	
				FD_SET(sd,&readfds);
			if(sd>max_sd)
				max_sd=sd;
		}		
		
		activity=select(max_sd+1,&readfds,NULL,NULL,&timeout);
		in_err(activity,"Error in select method!");
		
		if(FD_ISSET(mainsocket,&readfds))
		{
			newsocket=accept(mainsocket,NULL,NULL);
			in_err(newsocket,"Error in accept method!");
			fcntl(newsocket, F_SETFL, O_NONBLOCK);

			
			for (int i = 0; i< MAX_CLIENT; i++) 
            		{
                
				if( client_socket[i] == 0 )
                		{
                		    client_socket[i] = newsocket;
					break;
               	      	        }
        	         }
		 }
		 for(int i=0;i<MAX_CLIENT;i++){
			sd=client_socket[i];
			if(FD_ISSET(sd,&readfds)){
				recv_res=recv(sd,string,1024,0);	
				in_err(recv_res,"Error in recv method!");
		
				int resoult=stringConvertToArithmeticOperations(string);
				itoa(resoult,string);
				int send_res=send(sd,string,1024,0);
				in_err(send_res,"Error in send method!");
				close(sd);
				client_socket[i]=0;	
			}
		}			
		
	}
	close(mainsocket);
	return 0;


	
}
