#include "client.hpp"                                                                                                                                                                                           
#include <stdio.h>
#include <unistd.h>
#include <time.h>
int main(){

 	  while(1){ // E:0 W:2  S:3  N:1   Forward:F LEFT:L RIGHT:R
       	int p = pass("127.0.0.1",8700,'A',0,3,'L'); 
		printf("%d\n",p);
		if(p == 1){
			sleep(3);
        	printf("exit %d\n",pass("127.0.0.1",8700,'A',1,3,'L'));
	 		sleep(3);
	 	}
		usleep(500000);
	 }

		return 0;
}

