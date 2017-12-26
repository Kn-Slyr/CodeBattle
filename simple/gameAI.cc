#include <iostream>
#include <time.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>			// getpid,
#include <stdlib.h>
#include <stdio.h>

#include <signal.h>			// kill

#define MSG_SIZE 80

using namespace std;

const char WEAPON[3][10] = {"ROCK", "SCISSOR", "PAPER"};
char msg[MSG_SIZE];
int filedes_AI2GM, filedes_GM2AI;
int cnt;

void pipeInit();
int AILogic();

int main(void)
{
	cout<<"Game AI Start : "<<endl;

	pipeInit();
	for(int cnt=0; cnt<5; cnt++)
	{
		// wait for GM
		if(read(filedes_GM2AI, msg, MSG_SIZE)==-1) {
			printf("fail to read filedes_GM2AI\n");
			exit(1);
		}
		cout <<"\tGM's log : "<<msg<<endl;
	 	int choice = AILogic();

		cout<<"\t CPU : "<<WEAPON[choice]<<endl;
		msg[0] = choice + '0';
		msg[1] = '\0';

		if(write(filedes_AI2GM, msg, MSG_SIZE)==-1){
			printf("fail to write filedes_AI2GM\n");
			exit(1);
		}
	}
}

int AILogic()
{
	srand(time(NULL));
	for(int i=0; i<3; i++)
	{
		cout<<i+1<<"th useless loop"<<endl;
		for(int j=0; j<100000000; j++);
	}
	return rand()%3;
}

void pipeInit()
{
	if((filedes_GM2AI = open("./fifo_GM2AI", O_RDONLY)) < 0)
	{
		printf("fail to open fifo_GM2AI\n");
		exit(1);
	}

	if((filedes_AI2GM = open("./fifo_AI2GM", O_WRONLY)) < 0)
	{
		printf("fail to open fifo_AI2GM\n");
		exit(1);
	}
}
