// compile for gameJudger
// g++ -std=c++11 -o ./exe/gameJudge GameJudge.h GameJudge.cc GameLogic.h GameLogicForRSP.cc main.cc NamedPipe.h NamedPipe.cc
#include <iostream>
#include "GameJudge.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
		cout<<"command error..."<<endl;
	GameJudge judge = GameJudge(argv[1], argv[2]);

	int winner = judge.mainGameLoop();
	if(winner == 0)
		cout<< "draw game!"<<endl;
	else
		cout<<"winner is " << argv[winner]<<endl;
	return 0;
}
