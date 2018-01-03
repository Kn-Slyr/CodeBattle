#include "GameAIForRSP_templete.cc"

#include <cstdlib>
#include <ctime>

class GameAIForRSP : public AIForRSP_templete
{
public :
	GameAIForRSP(int playerNum)
		: AIForRSP_templete(playerNum)
	{
		srand(time(nullptr));
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
		isEnd = 1;

		// *check = 1;
	}

	// this is what user implement
	int userAILogic(int enemyLastWeapon)
	{
		int weapon = rand()%3;
		cout<<"\tmy choice is "<<weapon<<endl;
		return weapon;
	}
};
