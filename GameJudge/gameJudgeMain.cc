// compile for gameJudger
// g++ -std=c++11 -o ./exe/gameJudge GameJudge.h GameJudge.cc GameLogic.h GameLogicForRSP.cc gameJudgeMain.cc NamedPipe.h NamedPipe.cc
#include <iostream>
#include "GameJudge.h"
using namespace std;

// argv[1] = player1 name, argv[2] = player2 name
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cout<<"command error..."<<endl;
		return 0;
	}
	GameJudge judge = GameJudge(argv[1], argv[2]);

	int winner = judge.mainGameLoop();
	if(winner == 0)
		cout<< "draw game!"<<endl;
	else
		cout<<"winner is " << argv[winner]<<endl;

	return 0;
}
