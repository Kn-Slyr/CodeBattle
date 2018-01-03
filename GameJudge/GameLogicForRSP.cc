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
	int stageNum, stageIdx;
	int winCount[2];
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
		stageIdx = 0;
	}

	virtual void allocMemory()
	{
		privateList = new int*[2];
		for(int i=0; i<2; i++)
			privateList[i] = new int[1005];
	}

	virtual void flushMemory()
	{
		for(int i=0; i<2; i++)
			delete[] privateList[i];
		delete[] privateList;
	}

	virtual void zeroTurnPlay()
	{
		cout<<"zeroTurnPlay!"<<endl;
		for(int player=0; player<2; player++)
			if(isAI[player])
				pipe[player]->toss("No mean for this game\n");
	}

	virtual void oneTurnPlay()
	{
		string msg;
		int weapon, tempWin;

		// toss data to AI
		if(stageIdx == 0)
		{
			for(int player=0; player<2; player++)
				if(isAI[player])
					pipe[player]->toss(string("turn:0,"));
		}
		else
		{
			for(int player=0; player<2; player++)
				if(isAI[player])
					pipe[player]->toss(parseForToss(stageIdx, privateList[!player][stageIdx-1]));
		}

		// get data from AI
		for(int player=0; player<2; player++)
		{
			if(isAI[player])
			{
				pipe[player]->getMsg(msg);
				parseForGet(msg, weapon);
			}
			else
			{
				printf("%dth Turn, player %d input : ", stageIdx, player+1);
				scanf("%d", &weapon);
			}

			privateList[player][stageIdx] = weapon;
		}

		// judge for Rock vs Scissor vs Paper
		tempWin = -1;
		if(privateList[0][stageIdx] == ROCK)
		{
			if(privateList[1][stageIdx] == SCISSOR)
				tempWin = 0;
			else if(privateList[1][stageIdx] == PAPER)
				tempWin = 1;
		}
		else if(privateList[0][stageIdx] == SCISSOR)
		{
			if(privateList[1][stageIdx] == ROCK)
				tempWin = 1;
			else if(privateList[1][stageIdx] == PAPER)
				tempWin = 0;
		}
		else if(privateList[0][stageIdx] == PAPER)
		{
			if(privateList[1][stageIdx] == ROCK)
				tempWin = 0;
			else if(privateList[1][stageIdx] == SCISSOR)
				tempWin = 1;
		}

		// @@debugging....
		cout<<"turn "<<stageIdx<<" : "<<endl;
		cout<<"p1 : "<<privateList[0][stageIdx]<<" vs "<<privateList[1][stageIdx]<<" : p2"<<endl;
		if(tempWin== -1) cout<<"draw!"<<endl;
		else cout<<"winner is "<<tempWin+1<<endl;

		if(tempWin != -1)
			winCount[tempWin]++;
		stageIdx++;
	}

	virtual bool gameLogic(int &winner)
	{
		if(abs(winCount[0] - winCount[1]) > stageNum - stageIdx)
		{
			winner = winCount[0] > winCount[1] ? 1 : 2;
			return true;
		}
		else if(stageNum == stageIdx)
		{
			if(winCount[0] == winCount[1])
				winner = 0;
			else
				winner = winCount[0] > winCount[1] ? 1 : 2;
			return true;
		}

		return false;
	}

	// message's format is "turnCount,enemy's last weapon"
	string parseForToss(int stgIdx, int lastWeapon)
	{
		char msg[50];
		snprintf(msg, sizeof(msg),
			"%d,%d", stgIdx, lastWeapon);
		return string(msg);
	}

	// this game's msg is only one char(0, 1, 2)
	// 0 : rock, 1 : scissor, 2 : paper
	bool parseForGet(string &msg, int &weapon)
	{
		weapon = msg[2] - '0';
		if(weapon < 0 || weapon > 2)
			return false;
		return true;
	}

};
