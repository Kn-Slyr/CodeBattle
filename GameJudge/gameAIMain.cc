// compile for gameAI
// g++ -std=c++11 -o ./exe/gameAI GameAI.h GameAIForRSP_templete.cc GameAIForRSP_user.cc gameAIMain.cc main.cc NamedPipe.h NamedPipe.cc
#include <iostream>
#include "GameAIForRSP_user"
using namespace std;

// argv[2] = this AI's player num(1 or 2)
// @@todo argv[3] = gameLogic for this AI
int main(int argc, char *argv[])
{
	if(argv != 2)
	{
		cout<<"command error..."<<endl;
		return 0;
	}

	GameAI ai = new GameAIForRSP(argv[2]-'0');
	ai->playAI();
	delete ai;

	return 0;
}
