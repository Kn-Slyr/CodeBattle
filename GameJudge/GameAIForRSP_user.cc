#include "GameAIForRSP_templete.cc"

class GameAIForRSP : public AIForRSP_templete
{
public :
	GameAIForRSP(int playerNum)
		: AIForRSP_templete(playerNum)
	{

	}

private :
	// virtual void *oneTurnPlay(void *pArgv)
	virtual void oneTurnPlay()
	{
		int enemyLastWeapon;
		// int *check = (int*)pArgv;
		parseForGet(pipeMsg, enemyLastWeapon);

		int weaponChoice = userAILogic(enemyLastWeapon);
		pipeMsg = parseForToss(weaponChoice);

		// *check = 1;
	}

	// this is what user implement
	int userAILogic(int enemyLastWeapon)
	{
		return 0;
	}
};
