#include <string>
#include <ctime>
#include "GameJudge.h"

using namespace std;

// init for common values
GameJudge::GameJudge(string &player1, string &player2)
{
	srand(time(NULL));

	player[0] = player1;
	player[1] = player2;
	winCount[0] = winCount[1] = 0;
}

GameJudge::~GameJudge()
{
}

//
// return : 0 for draw, 1 for player1, 2 for player2
int GameJudge::mainGameLoop()
{
	for(int stg=0; stg<stageNum; stg++)
	{
		gameLogic = new RockScissorPaper();
		winCount[gameLogic.gamePlay()]++;
		delete gameLogic;
	}

	if(winCount[0] == winCount[1])	return 0;
	return (winCount[0] < winCount[1]) + 1;
}
