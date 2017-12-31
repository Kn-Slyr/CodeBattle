#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <cstdio>
#include "NamedPipe.h"

class GameLogic
{
protected :
	std::string gameName;

	int **privateList;		// privateList[player][idx]
	int *commonList;		// commonList[idx]
	int ***privateBoard;	// privateBoard[player][x][y]
	int **commonBoard;		// commonBoard[x][y]

	bool isAI[2];
	NamedPipe *pipe[2];

public :
	GameLogic(bool isAI1, bool isAI2)
	{
		printf("Load GameLogic...\n");

		isAI[0] = isAI1;
		isAI[1] = isAI2;

		for(int player=0; player<2; player++)
			if(isAI[player])
			{
				string tmp;
				NamedPipe::makeFifoFile(player);
				pipe[player] = new NamedPipe(player, true);
				pipe[player]->getMsg(tmp);	// wait for AI load
			}
	}

	~GameLogic()
	{
		printf("Close GameLogic...");

		for(int player=0; player<2; player++)
			if(isAI[player])
				delete pipe[player];
	}

	int gamePlay()
	{
		int winner;
		zeroTurnPlay();
		while(true)
		{
			oneTurnPlay();
			if(gameLogic(winner)) break;
		}
		return winner;
	}
	
private :
	// initiate basic game data
	virtual void setGameInfo() = 0;

	// allocate memory at ***list or ***board
	virtual void allocMemory() = 0;

	// free memory for allocated in upper function
	virtual void flushMemory() = 0;

	// transfer initial information to players
	virtual void zeroTurnPlay() = 0;

	// one turn for each players
	virtual void oneTurnPlay() = 0;

	// check for game end
	// winner=0 : draw, winner=1 : player1 win, winner=2 : player2 win
	// return : true for stage end, false for continue
	virtual bool gameLogic(int &winner) = 0;

	// string parseForToss(values) = 0;
	// bool parseForGet(&values) = 0;
};

#endif
