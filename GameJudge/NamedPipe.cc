#include "NamedPipe.h"

NamedPipe::NamedPipe(int playerNum, bool _isJudger)
{
	isJudger = _isJudger;
	// strcpy_s(fifoName, 11, "./fifo_AIX");
	strcpy(fifoName, "./fifo_AIX");
	fifoName[9] = '0' + playerNum;

	if((fileDes = open(fifoName, O_RDWR)) < 0)
	{
		printf("fail to open fifo_GM2AI\n");
		exit(1);
	}
}

NamedPipe::~NamedPipe()
{
	if(isJudger)
		unlink(fifoName);
}

void NamedPipe::toss(string msg)
{
	if(write(fileDes, msg.c_str(), MSG_SIZE) == -1)
	{
		printf("Fail to write() for %s\n", fifoName);
		exit(1);
	}
}

void NamedPipe::getMsg(string msg)
{
	char tmsg[80];
	if((read(fileDes, tmsg, MSG_SIZE)) < 0)
	{
		printf("Fail to read() for %s\n", fifoName);
		exit(1);
	}
	msg = string(tmsg);
}
