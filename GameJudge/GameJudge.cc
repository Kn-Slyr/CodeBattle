#include <string>
#include "GameJudge.h"

using namespace std;

// init for common values
GameJudge::GameJudge(string player1, string player2)
{
	player[0] = player1;
	player[1] = player2;
	winCount[0] = winCount[1] = 0;

	// init for every games
	initForGame();
}

GameJudge::~GameJudge()
{
	if(deleteDynamicAlloc & 1)
		delete[] privateList;
	if(deleteDynamicAlloc & 2)
		delete[] commonList;
	if(deleteDynamicAlloc & 4)
		delete[] privateBoard;
	if(deleteDynamicAlloc & 8)
		delete[] commonBoard;
}

//
// return : 0 for draw, 1 for player1, 2 for player2
int GameJudge::mainGameLoop()
{
	for(int stg=0; stg<stageNum; stg++)
	{
		winCount[oneStagePlay()]++;
	}

	if(winCount[0] == winCount[1])	return 0;
	return (winCount[0] < winCount[1]) + 1;
}
