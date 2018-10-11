#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int cpid;
	int start=0,end=100;
	int pipes[10][2];
	int Array[1000];
	for (int i=0;i<1000;i++)
		Array[i]=i+1;
	for (int i=0;i<10;i++){
		pipe(pipes[i]);
		cpid=fork();
		if (cpid==0){
			close(pipes[i][0]);
			int sum=0;
			for (int j=start;j<end;j++)
				sum=sum+Array[j];
			write(pipes[i][1],&sum,sizeof(sum));
			close(pipes[i][1]);
			exit(0);
		}
		else if (cpid>0){
			start=end;
			end=end+100;
		}
		else{
			return 0;
		}	
	}
	int total_sum=0;
	int sum=0;
	for (int i=0;i<10;i++){
		wait(NULL);
		read(pipes[i][0],&sum,sizeof(sum));
		total_sum=total_sum+sum;
	}
	printf("Total Sum from 10 Processes : %d",total_sum);
	return 0;
}
