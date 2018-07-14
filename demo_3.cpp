#include "client.hpp"                                                       
#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){
      //while(1){
          int p = pass("127.0.0.1",8700,'A',0,4,'F');
          printf("%d\n",p);
          if(p == 1){
              sleep(2);
              printf("exit %d\n",pass("127.0.0.1",8700,'B',0,4,'F'));
              sleep(5);
          }
          usleep(500000);
 		//}
 		return 0;
}

