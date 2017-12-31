#include <string>
#include <ctime>
#include "GameJudge.h"
#include "GameLogicForRSP.cc"

using namespace std;

// init for common values
GameJudge::GameJudge(string player1, string player2)
{
	srand(time(NULL));

	player[0] = player1;
	isAI[0] = (player[1][0] == 'A');
	player[1] = player2;
	isAI[1] = (player[2][0] == 'A');
	winCount[0] = winCount[1] = 0;
	stageNum = 1;
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
		// in this term, execute other AI exe files
		gameLogic = new RockScissorPaper(isAI[0], isAI[1]);
		int tmpWinner = gameLogic->gamePlay();
		if(tmpWinner) winCount[tmpWinner-1]++;
		delete gameLogic;
	}

	if(winCount[0] == winCount[1])	return 0;
	return (winCount[0] < winCount[1]) + 1;
}
