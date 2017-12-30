#include "GameLogic.h"

class RockScissorPaper : public gameLogic
{
	void setGameInfo()
	{
		gameName = "RockScissorPaper";
		stageNum = 1000;
	}

	void allocMemory()
	{
		privateList = new int*[2];
		for(int i=0; i<2; i++)
			privateList[i] = new int[1005];
	}

	void flushMemory()
	{
		for(int i=0; i<2; i++)
			delete[] privateList[i];
		delete[] privateList;
	}

	void zeroTurnPlay()
	{

	}

	void oneTurnPlay()
	{

	}

	// return : true for stage end, false for continue
	bool gameLogic(int &winner)
	{
		winner = 1;
		return true;
	}
}


bool parseForToss(string &msg)
{
}

bool parseForGet(string &msg)
{
}
