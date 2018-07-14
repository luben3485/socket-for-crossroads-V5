#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>  
#include "client.hpp"
//structure of sending data
/*
struct send_info{
	char car; //car name
	int status; // 0 enter   1 exit
	int in;  // E:0  W:2  S:3  N:1
	char dir; //F L R
};
class Socket{
	private:
		int sockfd;
	public:
		Socket(void);
		~Socket();
		void Connection(const char* addr,int port);
		void Send(char car,int status,int in,char dir);
		void Recv(char* receiveMessage);
};
*/
/*
int main(int argc , char *argv[])
{
	
	//Create Socket object
	Socket s;

	while(1){
		//Make connection with server
		s.Connection("127.0.0.1",8700);
	
		//Send message to server
		s.Send('A',0,0,'R');

		//receive message from server
	    char receiveMessage[1024] = {};
		s.Recv(receiveMessage);
   		printf("%s\n",receiveMessage);

	}
    return 0;
}
*/
int pass(const char* addr,int port,char car,int status,int in,char dir){
 	
	Socket s;
    return s.permission(addr,port,car,status,in,dir);

}
int Socket::permission(const char* addr,int port,char car,int status,int in,char dir){
 
        Connection(addr,port);

        Send(car,status,in,dir);
 
        //receive message from server
        char receiveMessage[1024] = {};
        Recv(receiveMessage);
        // printf("%s\n",receiveMessage);
		if(strcmp(receiveMessage,"GOGO") == 0){
			return 1;
		}else return 0;

}

  int Socket::parking(const char* addr,int port,char car,int status,int in,char dir){
   
          Connection(addr,port);
  
          Send(car,status,in,dir);
   
          //receive message from server
          char receiveMessage[1024] = {};
          Recv(receiveMessage);
          // printf("%s\n",receiveMessage);
          if(strcmp(receiveMessage,"GOGO") == 0){
              return 1;
          }else return 0;
  
  } 

void Socket::Recv(char* receiveMessage){

    //recv a message from server
	recv(sockfd,receiveMessage,sizeof(receiveMessage),0);

}
Socket::Socket(void){
	sockfd = -1;
}

Socket::~Socket(){
//	printf("close Socket\n");
    close(sockfd);
}
void Socket::Connection(const char* addr,int port){

    //socket的建立
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr(addr);
    info.sin_port = htons(port);


    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
    }


}
void Socket::Send(char car,int status,int in,char dir){
    //in 為路口編號(包含東西南北)
    //Send a message to server
	char snd_buf[1024] = {};
	struct send_info info1;
	info1.car = car;
	info1.status = status;
	info1.in = in;
	info1.dir = dir;
		
	memset(snd_buf,0,sizeof(snd_buf));
	memcpy(snd_buf,&info1,sizeof(info1));
	send(sockfd,snd_buf,sizeof(snd_buf),0);
}
