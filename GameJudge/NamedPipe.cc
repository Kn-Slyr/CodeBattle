#include "NamedPipe.h"

NamedPipe::NamedPipe(int playerNum, bool _isJudger)
{
	isJudger = _isJudger;
	// strcpy_s(fifoName, 14, "./fifo_AIXFor");
	strcpy(fifoName[TOSSER], "./fifo_AIXForToss");
	fifoName[TOSSER][9] = '0' + playerNum;
	strcpy(fifoName[GETTER], "./fifo_AIXForGet");
	fifoName[GETTER][9] = '0' + playerNum;

	// @@it have to open this order
	if(isJudger)
	{
		if((fileDes[TOSSER] = open(fifoName[TOSSER==isJudger], O_WRONLY)) < 0)
		{
			printf("fail to open %s\n", fifoName[TOSSER==isJudger]);
			exit(1);
		}

		if((fileDes[GETTER] = open(fifoName[GETTER==isJudger], O_RDONLY)) < 0)
		{
			printf("fail to open %s\n", fifoName[GETTER==isJudger]);
			exit(1);
		}
	}
	else
	{
		if((fileDes[GETTER] = open(fifoName[GETTER==isJudger], O_RDONLY)) < 0)
		{
			printf("fail to open %s\n", fifoName[GETTER==isJudger]);
			exit(1);
		}

		if((fileDes[TOSSER] = open(fifoName[TOSSER==isJudger], O_WRONLY)) < 0)
		{
			printf("fail to open %s\n", fifoName[TOSSER==isJudger]);
			exit(1);
		}
	}


	printf("pipe for player%d constructed\n", playerNum);
}

NamedPipe::~NamedPipe()
{
	if(isJudger)
	{
		unlink(fifoName[TOSSER]);
		unlink(fifoName[GETTER]);
	}
}

void NamedPipe::toss(string msg)
{
	if(write(fileDes[TOSSER], msg.c_str(), MSG_SIZE) == -1)
	{
		printf("Fail to write() for %s\n", fifoName[TOSSER]);
		exit(1);
	}
}

void NamedPipe::getMsg(string &msg)
{
	char tmsg[80];
	if((read(fileDes[GETTER], tmsg, MSG_SIZE)) < 0)
	{
		printf("Fail to read() for %s\n", fifoName[GETTER]);
		exit(1);
	}
	msg = string(tmsg);
}
