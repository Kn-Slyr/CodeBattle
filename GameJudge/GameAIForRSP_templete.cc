#include "GameAI.h"

class AIForRSP_templete : public GameAI
{
private :
	int stageNum;
	int stageIdx;
public :
	AIForRSP_templete(int playerNum)
		: GameAI(playerNum)
	{
		allocMemory();
		setGameInfo();
	}

private :
	virtual void setGameInfo()
	{
		gameName = "RockScissorPaper";
		stageNum = 1000;
		stageIdx = 0;
	}

	virtual void allocMemory()
	{
		// do nothing
	}

	virtual void flushMemory()
	{
		// do nothing
	}

	virtual void zeroTurnPlay()
	{
		// do nothing to initialize
	}

	// this function is what user have to implement
	virtual bool oneTurnPlay() = 0;

protected :
	string parseForToss(int choiceWeapon)
	{
		char msg[50];
		snprintf(msg, sizeof(msg),
			"%d,%d", turnCount, choiceWeapon);
		return string(msg);
	}

	bool parseForGet(string &msg, int &lastEnemyWeapon)
	{
		return true;
	}
};
