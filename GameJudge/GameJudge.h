#include <string>
#include "GameLogic.h"

class GameJudge
{
// codes in GameJudge.cc file
private :
	std::string player[2];	// user : U_userid, AI : A_uploadPn
	bool isAI[2];
	GameLogic *gameLogic;
	int winCount[2];
	int stageNum;

public :
	GameJudge(string player1, string player2);
	~GameJudge();
	int mainGameLoop();
};
