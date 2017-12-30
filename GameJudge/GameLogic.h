#include <cstdio>
#include "NamedPipe.h"

class GameLogic
{
private :
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
				pipe[player] = new NamedPipe(player, true);

		allocMemory();
		setGameInfo();

	}
	~GameLogic()
	{
		printf("Close GameLogic...");

		flushMemory();

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

	// initiate basic game data
	virtual void setGameInfo();

	// allocate memory at ***list or ***board
	virtual void allocMemory();

	// free memory for allocated in upper function
	virtual void flushMemory();

	// transfer initial information to players
	virtual void zeroTurnPlay();

	// one turn for each players
	virtual void oneTurnPlay();

	// check for game end
	// return : true for stage end, false for continue
	virtual bool gameLogic(int &winner);
}
