// g++ -std=c++11 -o ./exe/gameJudger *.cc
#include <iostream>
#include "GameJudge.h"
using namespace std;

int main(int argc, char *argv[])
{
	if(argc != 3)
		cout<<"miss command..."<<endl;
	GameJudge judge = GameJudge(argv[1], argv[2]);

	int winner = judge.mainGameLoop();
	cout<<"winner is player" << winner<<"...!"<<endl;
	return 0;
}
