#include <sys/types.h>
#include <sys/socket.h>
#include <json-c/json.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 8888
#define ADDRESS "127.0.0.1"
#define true 1

void in_err(int n,char * message){
	if(n<0){
		perror(message);
		exit(1);
	}
}
void createJsonFile(char * filename){
	
	FILE * file;
	file=fopen(filename,"w+");
	char message[]="Hello server!",task[1024];
	printf("\nEnter task:");
	scanf("%s",task);
	printf("\n");
	
	struct json_object * obj=json_object_new_object();
	struct json_object *jmess=json_object_new_string(message);
	struct json_object *jtask=json_object_new_string(task);

	json_object_object_add(obj,"Message",jmess);
	json_object_object_add(obj,"Task",jtask);

	const char * json_st=json_object_to_json_string(obj);
	fwrite(json_st,strlen(json_st),1,file);
	fclose(file);
}
int main(){

	FILE * file;
	createJsonFile("jsonfile.json");
	file=fopen("jsonfile.json","r+");
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
				
		fread(string,1024,1,file);
	
		int send_res=send(mainsocket,string,1024,0);
		in_err(send_res,"Error in send method!");
		
		recv_res=recv(mainsocket,string,1024,0);	
		in_err(recv_res,"Error in recv method!");

		fwrite(string,strlen(string),1,file);
		
		struct json_object * parsed_json;
		struct json_object * resoult;
		struct json_object * message;

		parsed_json=json_tokener_parse(string);
		json_object_object_get_ex(parsed_json,"Resoult",&resoult);
		json_object_object_get_ex(parsed_json,"Message",&message);
		
		printf("Server message:%s",json_object_get_string(message));
		printf("\n");
		printf("Resoult:%s\n",json_object_get_string(resoult));
		break;			
		
	}
	close(mainsocket);
	return 0;


	
}
