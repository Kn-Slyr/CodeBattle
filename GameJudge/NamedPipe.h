#ifndef __NAMED_PIPE_H__
#define __NAMED_PIPE_H__

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#include <sys/stat.h>		// mkfifo
#include <fcntl.h>			// O_RDWR
#include <unistd.h>			// unlink
// #include <io.h>				// access, remove
#define MODE 0666
#define MSG_SIZE 80
#define TOSSER 	0
#define GETTER 	1
using namespace std;

class NamedPipe
{
private :
	bool isJudger;
	int fileDes[2];
	char fifoName[2][20];

	template<typename Out>
	void split(const std::string &s, char delim, Out result);

public :
	NamedPipe(int playerNum, bool _isJudger);
	~NamedPipe();
	void toss(string msg);
	void getMsg(string &msg);
	void getSplittedMsg(vector<string> &splittedMsg, const string &s, char delim = ' ');

	// this function have to call before make new instance
	static void makeFifoFile(int playerNum)
	{
		char fifoName[2][20] = { "./fifo_AIXForToss", "./fifo_AIXForGet"};

		for(int who=TOSSER; who<=GETTER; who++)
		{
			fifoName[who][9] = '0' + playerNum;
			printf("%s\n", fifoName[who]);

			// if file already exist, delete it
			if(access(fifoName[who], 00) == 0)
				unlink(fifoName[who]);

			if(mkfifo(fifoName[who], MODE) == -1)
			{
				printf("fail to make fifo for %s\n", fifoName[who]);
				exit(1);
			}
		}
	}
	// static void makeFifoFile(int playerNum)
	// {
	// 	char fifoTossName[] = "./fifo_AIXForToss";
	// 	char fifoGetName[] = "./fifo_AIXForGet";
	// 	fifoTossName[9] = '0' + playerNum;
	// 	fifoGetName[9] = '0' + playerNum;
    //
	// 	if(mkfifo(fifoTossName, MODE) == -1)
	// 	{
	// 		printf("fail to make fifo for AI%d\n", playerNum);
	// 		exit(1);
	// 	}
	// 	else if(mkfifo(fifoGetName, MODE) == -1)
	// 	{
	// 		printf("fail to make fifo for AI%d\n", playerNum);
	// 		exit(1);
	// 	}
	// }
};

#endif
