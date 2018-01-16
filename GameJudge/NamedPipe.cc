#include "NamedPipe.h"

NamedPipe::NamedPipe(int playerNum, bool _isJudger)
{
	isJudger = _isJudger;
	// strcpy_s(fifoName, 14, "./fifo_AIXFor");
	strcpy(fifoName[TOSSER], "./fifo_AIXForToss");
	fifoName[TOSSER][9] = '0' + playerNum;
	strcpy(fifoName[GETTER], "./fifo_AIXForGet");
	fifoName[GETTER][9] = '0' + playerNum;

	int authFlag[2] = {O_WRONLY, O_RDONLY};

	// it has to open this order
	if(isJudger)
	{
		for(int who = TOSSER; who <= GETTER; who++)
		{
			if((fileDes[who] = open(fifoName[who==isJudger], authFlag[who])) < 0)
			{
				printf("fail to open %s\n", fifoName[who==isJudger]);
				exit(1);
			}
		}
	}
	else
	{
		for(int who = GETTER; who >= TOSSER; who--)
		{
			if((fileDes[who] = open(fifoName[who==isJudger], authFlag[who])) < 0)
			{
				printf("fail to open %s\n", fifoName[who==isJudger]);
				exit(1);
			}
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

void NamedPipe::getSplittedMsg(vector<string> &splittedMsg, char delim)
{
	string originMsg;
	getMsg(originMsg);

	splittedMsg.clear();
    split(originMsg, delim, back_inserter(splittedMsg));
}

template<typename Out>
void NamedPipe::split(const string &originMsg, char delim, Out result)
{
	stringstream sstream = stringstream(originMsg);
	string item;
	while (std::getline(sstream, item, delim))
		*(result++) = item;
}
