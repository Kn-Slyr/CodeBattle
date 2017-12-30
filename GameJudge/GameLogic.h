
class GameLogic
{
private :
	std::string gameName;

	int stageNum;
	int **privateList;		// privateList[player][idx]
	int *commonList;		// commonList[idx]
	int ***privateBoard;	// privateBoard[player][x][y]
	int **commonBoard;		// commonBoard[x][y]

	bool isAI[2];
	NamedPipe *pipe[2];

public :
	GameLogic(bool isAI1, bool isAI2)
	{
		isAI[0] = isAI1;
		isAI[1] = isAI2;

		for(int i=0; 0<2; i++)
			if(isAI[i])
				pipe[i] = new NamedPipe(i, true);

		allocMemory();
		setGameInfo();

	}
	~GameLogic()
	{
		flushMemory();
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

	virtual void setGameInfo();
	virtual void allocMemory();
	virtual void flushMemory();
	virtual void zeroTurnPlay();
	virtual void oneTurnPlay();
	virtual bool gameLogic(int &winner);
}
