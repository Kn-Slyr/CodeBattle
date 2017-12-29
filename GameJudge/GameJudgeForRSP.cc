#include "GameJudge.h"

void GameJudge::initForGame()
{
	gameName = "RockScissorPaper";
	stageNum = 1000;

	deleteDynamicAlloc = 0;
	deleteDynamicAlloc += 1;
	privateList = new int[2][1000];
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
bool gameLogic(ref int winner)
{
	return true;
}
