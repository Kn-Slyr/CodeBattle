#include <string>
#define MODE 0666
using namespace std;

class NamedPipe
{
private :
	bool isJudger;
	int fileDes;
	char fifoName[40];

public :
	NamedPipe(int playerNum, bool _isJudger);
	~NamedPipe();
	void toss(string &msg);
	void get(string &msg);

	static void makeFifoFile(int playerNum)
	{
		char fifoName[] = "./fifo_AIX";
		fifoName[9] = '0' + playerNum;
		if(mkfifo(fifoName, MODE) == -1)
		{
			printf("fail to make fifo for AI%d\n", playerNum);
			exit(1);
		}
	}
};
