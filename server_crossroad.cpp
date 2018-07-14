#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


//sending data from client

struct send_info 
{
	char car; //車子ID
	int status; //0 enter 1 exit
	int in; //進入 E:0  W:2  S:3  N:1 park : 4
	char dir;// direction   L-left  R-right F-forward
};

class Crossroads{
	private:
		int sys_path[4];
        int sys_seets[4];

	public:
		Crossroads();
		int permission(send_info info);
        int parking(send_info clt);
		void remove(send_info info);

};

Crossroads::Crossroads(){
	sys_path[0] = 0;
	sys_path[1] = 0;
	sys_path[2] = 0;
	sys_path[3] = 0;
    sys_seets[0] = 0;
	sys_seets[1] = 0;

}

int Crossroads::permission(send_info clt){
	int in = clt.in;
	if(clt.dir == 'R'){ 
		if(sys_path[in] == 1) return 0;
		else{
			sys_path[in] = 1;
		}
	}else if(clt.dir == 'F'){
		if(sys_path[in] == 1 || sys_path[(in + 1) %4] == 1) return 0;
		else{
			sys_path[in] = 1;
			sys_path[(in + 1) %4] = 1;
			return 1;
		}
		
	
	}else if(clt.dir == 'L'){
		if(sys_path[in] == 1 || sys_path[(in + 1) %4] == 1 || sys_path[(in + 2) %4] == 1 ) return 0;
		else{
			sys_path[in] = 1;
			sys_path[(in + 1) %4] = 1;
			sys_path[(in + 2) %4] = 1;
			return 1;
		}
	
	}	

}

void Crossroads::remove(send_info clt){
	int in = clt.in;
	if(clt.dir == 'R'){
		sys_path[in] = 0; 

	}else if(clt.dir == 'F'){
		sys_path[in] = 0;
		sys_path[(in + 1) %4] = 0; 

	}else if(clt.dir == 'L'){

		sys_path[in] = 0;	
		sys_path[(in + 1) %4] = 0; 
		sys_path[(in + 2) %4] = 0; 
	}	

}

int Crossroads::parking(send_info clt){
    
	 for( int a = 0; a < 2; a++ )
                   {
                       if(sys_seets[a]==0){
                           sys_seets[a]=1;
                           return a;
                           break;
                       }
                   }


}

int main(int argc , char *argv[])

{
    //socket的建立
    char recv_buf[1024] = {};
//	char message[] = {"Hi,this is server.\n"};
   	send_info clt;
   	int sockfd = 0,forClientSockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.\n");
    }

    //socket的連線
    struct sockaddr_in serverInfo,clientInfo;
    socklen_t addrlen = sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));

    serverInfo.sin_family = PF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8700);
    bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    listen(sockfd,5);

	//Crossroads object
	Crossroads crossroads;

    while(1){
        forClientSockfd = accept(sockfd,(struct sockaddr*) &clientInfo, &addrlen);

   		memset(recv_buf,0,sizeof(recv_buf));
		recv(forClientSockfd,recv_buf,sizeof(recv_buf),0);
        memset(&clt,0,sizeof(clt));
		memcpy(&clt,recv_buf,sizeof(clt));
		
      
        if(clt.in == 4){
             if(crossroads.parking(clt)==1){
                        char message[] = {"GOGO"};			
                        send(forClientSockfd,message,sizeof(message),0);
                    }else{
                        char message[] = {"WAIT"};			
                        send(forClientSockfd,message,sizeof(message),0);	
                    }
                    printf("Client information: ");	
                    printf("Car:%c ",clt.car);
                    printf("Status:%d ",clt.status);
                    printf("In:%d ",clt.in);
                    printf("Dir:%c\n",clt.dir); 
            
            
        }else{
             if(clt.status == 0 ){
                    if(crossroads.permission(clt)==1){
                        char message[] = {"GOGO"};			
                        send(forClientSockfd,message,sizeof(message),0);
                    }else{
                        char message[] = {"WAIT"};			
                        send(forClientSockfd,message,sizeof(message),0);	
                    }
                    printf("Client information: ");	
                    printf("Car:%c ",clt.car);
                    printf("Status:%d ",clt.status);
                    printf("In:%d ",clt.in);
                    printf("Dir:%c\n",clt.dir); 

                }else if(clt.status == 1 ){
                    crossroads.remove(clt);
                    char message[] = {"BYE"};			
                    send(forClientSockfd,message,sizeof(message),0);	
                    printf("Client information: %d car has left!",clt.car);
                }        
        }
               
		
   
	}
    return 0;
}
