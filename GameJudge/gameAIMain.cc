// compile for gameAI
// g++ -std=c++11 -o ./exe/gameAI GameAI.h GameAIForRSP_templete.cc GameAIForRSP_user.cc gameAIMain.cc NamedPipe.h NamedPipe.cc MacroForPlay.h -pthread
#include <iostream>
#include "GameAIForRSP_user.cc"
using namespace std;

// argv[2] = this AI's player num(0 or 1)
// @@todo argv[3] = gameLogic for this AI
int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		cout<<"command error..."<<endl;
		return 0;
	}

	GameAI *ai = new GameAIForRSP(argv[1][0]-'0');
	ai->playAI();
	delete ai;

	return 0;
}
