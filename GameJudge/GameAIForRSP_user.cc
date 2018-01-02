#include "GameAIForRSP_templete.cc"

class GameAIForRSP : public AIForRSP_templete
{
public :
	GameAIForRSP(int playerNum)
		: AIForRSP_templete(playerNum)
	{

	}

private :
	virtual bool oneTurnPlay()
	{
		// get message part
		string msg;
		int enemyLastWeapon;
		pipe->getMsg(msg);
		parseForGet(msg, enemyLastWeapon);

		int weaponChoice = userAILogic(enemyLastWeapon);
		msg = parseForToss(weaponChoice);
		pipe->toss(msg);
	}

	// this is what user implement
	int userAILogic(int enemyLastWeapon)
	{
		return 0;
	}
};
