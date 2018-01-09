#include <sstream>
#include "GameAI.h"

class AIForRSP_templete : public GameAI
{
private :
	int stageNum;
	int stageIdx;

protected :
	int choiceWeapon;
	int enemyLastWeapon;

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

	// this function is what user have to implement in GameAIForRSP_user.cc
	virtual void oneTurnPlay() = 0;

	virtual bool isValidChoice()
	{
		return choiceWeapon < 0 || choiceWeapon > 2;
	}

protected :
	// msg will be made by format "turn number, choosen weapon"
	virtual void parseForToss()
	{
		char msg[50];
		snprintf(msg, sizeof(msg), "%d,%d", turnCount, choiceWeapon);
		pipeMsg = string(msg);
	}

	// message's format is "turn number, enemy's last weapon"
	virtual void parseForGet()
	{
		// set enemyLastWeapon
		 istringstream sstream = istringstream(pipeMsg);
		 string tmp;
		 for(int i=0; i<2 && sstream; i++)
		 {
			 sstream >> tmp;
			 switch(i)
			 {
				case 0 :
				 	break;
				case 1 :
					enemyLastWeapon = stoi(tmp);
					break;
				default :
					return;
			 }
		 }
	}
};
