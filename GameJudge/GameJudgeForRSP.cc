#include "GameJudge.h"

void GameJudge::initForGame()
{
	gameName = "RockScissorPaper";
	stageNum = 1000;

	privateList = new int*[2];
	for(int i=0; i<2; i++)
		privateList[i] = new int[stageNum];
}

void GameJudge::flushMemory()
{
	for(int i=0; i<2; i++)
		delete[] privateList[i];
	delete[] privateList;
}

int GameJudge::oneStagePlay()
{
	int winner;
	initForStage();
	while(true)
	{

		// pipe
		if(gameLogic(winner)) break;
	}
	return winner;
}

void GameJudge::oneTurnPlay()
{

}

// return : true for stage end, false for continue
bool GameJudge::gameLogic(int winner)
{
	return true;
}

bool parseForToss(string &msg)
{
}

bool parseForGet(string &msg)
{
}
