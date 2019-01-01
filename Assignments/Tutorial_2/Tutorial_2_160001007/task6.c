#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
	int segment_id = shmget(IPC_PRIVATE,1024,0666|IPC_CREAT);
	printf("Segment ID : %ld\n",segment_id);
	char* c=(char*) shmat(segment_id,NULL,0);
	strcat(c,"Hello\n");
	int pid=fork();
	if (pid==0)
	{
		int id=fork();
		if (id==0)
		{
			char* c=(char*) shmat(segment_id,NULL,0);
			strcat(c,"Hii\n");
		}
		else
		{
			wait(NULL);
			char* c=(char*) shmat(segment_id,NULL,0);
			strcat(c,"Hi\n");	
		}
	}
	else
	{
		wait(NULL);
		char* c=(char*) shmat(segment_id,NULL,0);
		printf("%s\n", c);
	}
	return 0;
}
