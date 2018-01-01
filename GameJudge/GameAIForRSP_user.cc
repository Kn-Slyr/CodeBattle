#include "GameAIForRSP_templete.h"

class GameAIForRSP : public AIForRSP_templete
{
private :
	virtual bool oneTurnPlay()
	{
		// get message part
		string msg;
		int enemylastWeapon;
		pipe->getMsg(msg);
		praseForGet(msg, enemyLastWeapon);

		int weaponChoice = userAILogic(enemyLastWeapon);
		msg = praseForToss(weaponChoice);
		pipe->toss(msg);
	}

	// this is what user implement
	int userAILogic(int enemyLastWeapon)
	{
		return 0;
	}
};
