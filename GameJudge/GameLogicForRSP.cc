#include <iostream>
#include <cstdlib>
#include "GameLogic.h"

#define ROCK 	0
#define SCISSOR 1
#define PAPER	2

using namespace std;

class LogicForRSP : public GameLogic
{
private :
	int stageNum, choiceWeapon;
	int winCount[2];
	int firstPlay;
	static constexpr const char* WEAPON[3] =
		{ "ROCK", "SCISSOR", "PAPER" };

public :
	LogicForRSP(bool isAI1, bool isAI2)
		: GameLogic(isAI1, isAI2)
	{
		allocMemory();
		setGameInfo();
	}

	~LogicForRSP()
	{
		flushMemory();
	}

private :
	virtual void setGameInfo()
	{
		gameName = "RockScissorPaper";
		stageNum = 9;
	}

	virtual void allocMemory()
	{
		privateList = new int*[2];
		int playerNum = getPlayerNum();
		for(int player=PLAYER0; player<playerNum; player++)
			privateList[player] = new int[1005];
	}

	virtual void flushMemory()
	{
		int playerNum = getPlayerNum();
		for(int player=PLAYER0; player<playerNum; player++)
			delete[] privateList[player];
		delete[] privateList;
	}

	virtual void zeroTurnPlay()
	{
		cout<<getWhoTurn()<<"\'s zeroTurnPlay!"<<endl;
	}

	virtual void playGameLogic()
	{
		int tempWin;
		const int turnCount = getTurnCount();
		privateList[getWhoTurn()][turnCount] = choiceWeapon;

		cout<<"turn info : "<<turnCount<<" : " << getWhoTurn()<<endl;
		cout<<privateList[0][turnCount]<<" : " <<privateList[1][turnCount]<<endl;
		// not ready for calc
		if(privateList[0][turnCount] == -1 || privateList[1][turnCount] == -1)
			return;

		// judge for Rock vs Scissor vs Paper
		tempWin = -1;
		if(privateList[0][turnCount] == ROCK)
		{
			if(privateList[1][turnCount] == SCISSOR)
				tempWin = 0;
			else if(privateList[1][turnCount] == PAPER)
				tempWin = 1;
		}
		else if(privateList[0][turnCount] == SCISSOR)
		{
			if(privateList[1][turnCount] == ROCK)
				tempWin = 1;
			else if(privateList[1][turnCount] == PAPER)
				tempWin = 0;
		}
		else if(privateList[0][turnCount] == PAPER)
		{
			if(privateList[1][turnCount] == ROCK)
				tempWin = 0;
			else if(privateList[1][turnCount] == SCISSOR)
				tempWin = 1;
		}

		cout<<"turn "<<turnCount<<" : "<<endl;
		cout<<"p1 : "<<privateList[0][turnCount]<<" vs "<<privateList[1][turnCount]<<" : p2"<<endl;
		if(tempWin== -1) cout<<"draw!"<<endl;
		else cout<<"winner is "<<tempWin+1<<endl;

		if(tempWin != -1)
			winCount[tempWin]++;

		checkGameEnd();
	}

	virtual bool checkGameEnd()
	{
		if(abs(winCount[0] - winCount[1]) > stageNum - getTurnCount())
		{
			setWinner(winCount[0] > winCount[1] ? 1 : 2);
			return true;
		}
		else if(stageNum == getTurnCount())
		{
			if(winCount[0] == winCount[1])
				setWinner(0);
			else
				setWinner(winCount[0] > winCount[1] ? 1 : 2);
			return true;
		}


		return false;
	}

	// message's format is "turnCount,enemy's last weapon"
	virtual string makeMsgForToss()
	{
		char msg[50];
		const int turnCount = getTurnCount();

		if(turnCount > 0)
			snprintf(msg, sizeof(msg), "%d:%d", turnCount, privateList[!getWhoTurn()][turnCount-1]);
		else if(turnCount == -1)
			return CodeReader::NOMEAN;
		else if(turnCount == 0)
			snprintf(msg, sizeof(msg), "%d:%d", turnCount, -1);
		return string(msg);
	}

	// this game's msg is only one char(0, 1, 2)
	// 0 : rock, 1 : scissor, 2 : paper
	virtual void parseForGet()
	{
		// normally use like this
		int len = getSplittedMsg().size();
		for(int i=0; i<len; i++)
		{
			string one = getSplittedMsg()[i];
			switch(i)
			{
			case 0 :
				break;
			case 1 :
				choiceWeapon = one[0] - '0';
				break;
			}
		}
	}

	virtual void turnInit()
	{
		privateList[PLAYER0][getTurnCount()] = -1;
		privateList[PLAYER1][getTurnCount()] = -1;
	}

	virtual bool isValidMsg()
	{
		return true;
	}
};
