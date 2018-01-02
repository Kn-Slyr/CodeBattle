#include <iostream>
#include <string>
#include "NamedPipe.h"

using namespace std;

class GameAI
{
protected :
	std::string gameName;
	int timeLimit;
	int myNumber;
	int turnCount;

	NamedPipe *pipe;

	int *privateList;		// privateList[player][idx]
	int **privateBoard;		// privateBoard[player][x][y]

public :
	GameAI(int playerNum)
	{
		cout<<"\tLoad GameAI...\n"<<endl;

		myNumber = playerNum;
		pipe = new NamedPipe(playerNum, false);

		readyToPlay();
	}

	~GameAI()
	{
		cout<<"\tClose GameAI...\n"<<endl;
		delete pipe;
	}

	void readyToPlay()
	{
		std::string msg = "AI numberX on ready...";
		msg[9] = '0' + myNumber;
		pipe->toss(msg);
	}

	void playAI()
	{
		zeroTurnPlay();
		while(oneTurnPlay());
	}

private :
	// get message from GameJudge
	// set initial info of game
	virtual void zeroTurnPlay() = 0;

	// get message from GameJudge(if get game end message, return false)
	// execute user's ai(analyze message, what to do)
	// toss message to GameJudge and return true
	virtual bool oneTurnPlay() = 0;
};
