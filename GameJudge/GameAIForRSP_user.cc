#include <cstdlib>
#include <ctime>

#include "GameAIForRSP_templete.cc"

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

		choiceWeapon = userAILogic();
		usedTimeUpdate(0);
		isFinishLogic = true;
	}

	// this is what user implement
	int userAILogic()
	{
		int weapon = rand()%3;
		cout<<"\tmy choice is "<<weapon<<endl;
		return weapon;
	}
};
