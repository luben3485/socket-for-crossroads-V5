//structure of sending data
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
		  int permission(const char* addr,int port,char car,int status,int in,char dir);
		  int parking(const char* addr,int port,char car,int status,int in,char dir);
  };
int  pass(const char* addr,int port,char car,int status,int in,char dir);



