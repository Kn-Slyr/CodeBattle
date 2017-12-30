#include <cstdlib>
#include "GameLogic.h"
#define ROCK 	0
#define SCISSOR 1
#define PAPER	2

class RockScissorPaper : public gameLogic
{
private :
	int stageNum, stageIdx;
	int winCount[2];
	const static WEAPON[3] = {"Rock", "Scissor", "Paper"};

public :
	virtual void setGameInfo()
	{
		gameName = "RockScissorPaper";
		stageNum = 1000;
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
		// do nothing for this game
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
					pipe[player]->toss("turn:0,");
		}
		else
		{
			for(int player=0; player<2; player++)
				if(isAI[player])
					pipe[player]->toss(parseForToss(player));
		}

		// get data from AI
		for(int player=0; player<2; player++)
		{
			if(isAI[player])
			{
				pipe[player]->get(msg);
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

		if(tempWin != -1)
			winCount[tempWin]++;
		stageIdx++;
	}

	virtual bool gameLogic(int &winner)
	{
		if(abs(winCount[0] - winCount[1]) > stageNum - stageIdx)
		{
			winner = winCount[0] > winCount[1] ? 0 : 1;
			return true;
		}
		return false;
	}

	string parseForToss(int player)
	{
		return "";
	}

	bool parseForGet(string &msg, int &weapon)
	{
		return true;
	}
}
