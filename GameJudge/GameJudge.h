#include <string>
#include "NamedPipe.h"

class GameJudge
{
// codes in GameJudge.cc file
private :
	std::string player[2];	// val : userId_uploadPN
	int winCount[2];
public :
	GameJudge();
	~GameJudge();
	int mainGameLoop();

// codes in GameJudgeFor__GAMENAME__.cc file
private :
	std::string gameName;
	int stageNum;
	char deleteDynamicAlloc;	// use 4bits for under pointers
	int **privateList;		// privateList[player][idx]
	int *commonList;		// commonList[idx]
	int ***privateBoard;	// privateBoard[player][x][y]
	int **commonBoard;		// commonBoard[x][y]
public :
	void initForGame();
	void initForStage();
	int oneStagePlay();
	void oneTurnPlay();
	bool gameLogic(ref int winner);
}
