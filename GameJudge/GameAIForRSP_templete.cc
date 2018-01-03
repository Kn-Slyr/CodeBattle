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
		setTimeChecker();
	}

private :
	virtual void setGameInfo()
	{
		gameName = "RockScissorPaper";
		stageNum = 9;
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

	virtual void setTimeChecker()
	{
		timeLimit = 2;
		// timeChecker = new TimeChecker(2);
	}

	virtual void zeroTurnPlay()
	{
		cout<<"\tzeroTurnPlay..."<<endl;
		pipe->getMsg(pipeMsg);
		cout<<"\tgetMsg:"<<pipeMsg<<endl;
	}

	// this function is what user have to implement
	// virtual void *oneTurnPlay(void *pArgv) = 0;
	virtual void oneTurnPlay() = 0;

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
