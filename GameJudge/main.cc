// g++ -std=c++11 -o ./exe/gameManager gameManager.cc
#include <iostream>
#include <cstring>

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define MSG_SIZE 80
using namespace std;

char msg[MSG_SIZE];
int filedes_AI2GM, filedes_GM2AI;

void pipeInit();
void pipeClose();
void mainGameLoop();
int parsing();

int main(void)
{
	pipeInit();
	mainGameLoop();
	pipeClose();
}

void pipeInit()
{
	cout<<"pipe Init start"<<endl;
	// from GameMaker to AI
	if(mkfifo("./fifo_GM2AI",0666) == -1)
	{
		printf("fail to make fifo_GM2AI\n");
		exit(1);
	}

	cout<<"this1?"<<endl;	// why stop in here?
	if((filedes_GM2AI = open("./fifo_GM2AI", O_RDWR)) < 0)
	// if((filedes_GM2AI = open("./fifo_GM2AI", O_WRONLY)) < 0)
	{
		printf("fail to open fifo_GM2AI\n");
		exit(1);
	}

	cout<<"this2?"<<endl;
	// from AI to GameManager
	if(mkfifo("./fifo_AI2GM",0666) == -1)
	{
		printf("fail to make  fifo_AI2GM\n");
		exit(1);
	}

	cout<<"this3?"<<endl;
	// if((filedes_AI2GM = open("./fifo_AI2GM", O_RDONLY)) < 0)
	if((filedes_AI2GM = open("./fifo_AI2GM", O_RDWR)) < 0)
	{
		printf("fail to open fifo_AI2GM\n");
		exit(1);
	}

	cout<<"pipe Init Fin"<<endl;
}

void pipeClose()
{
	unlink("./fifo_GM2AI");
	unlink("./fifo_AI2GM");
}

void mainGameLoop()
{
	int p1, p2, winCnt1, winCnt2;
	const char WEAPON[3][10] = {"ROCK", "SCISSOR", "PAPER"};

	cout<<"Game Start!"<<endl;
	for(int cnt=0; cnt<5; cnt++)
	{
		cout << "Turn "<<cnt+1<< " : "<<endl;
		p1 = -1;
		while(!(0<= p1 && p1 <=2))
		{
			cout<<"\tYour turn, input(Rock: 0, Scissor: 1, Paper:2) : ";
			cin>>p1;
		}

		cout<<"\tCPU turn, wait a seconds..."<<endl;
		// wake up Game AI
		strcpy(msg, "(game log from GM)");
		msg[MSG_SIZE-1] = '\0';
		if(write(filedes_GM2AI, msg, MSG_SIZE)==-1){
			printf("fail to call write()\n");
			exit(1);
		}
		if((read(filedes_AI2GM, msg, MSG_SIZE)) < 0 ){
			printf("fail to call read()\n");
			exit(1);
		}

		p2 = parsing();
		cout << "You : " << WEAPON[p1]<<" VS " << WEAPON[p2]<<" : CPU"<<endl;
	}
}

int parsing()
{
	printf("\trecv: %s\n", msg);
	return msg[0] - '0';	// 012 : OK, -1 : late
}
