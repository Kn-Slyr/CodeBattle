#include <iostream>
#include <cstdlib>
#include "GameLogic.h"

#define ROCK 	0
#define SCISSOR 1
#define PAPER	2

using namespace std;

//
//

class LogicForRSP : public GameLogic
{
private :
	int stageNum, stageIdx, choiceWeapon;
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
		stageIdx = 0;

		stageInit();
	}

	virtual void allocMemory()
	{
		privateList = new int*[2];
		for(int player=PLAYER0; player<playerNum; player++)
			privateList[player] = new int[1005];
	}

	virtual void flushMemory()
	{
		for(int player=PLAYER0; player<playerNum; player++)
			delete[] privateList[player];
		delete[] privateList;
	}

	virtual void zeroTurnPlay()
	{
		cout<<"zeroTurnPlay!"<<endl;
		for(int player=PLAYER0; player<playerNum; player++)
			if(isAI[player])
				pipe[player]->toss("No mean for this game\n");
	}

	virtual void playGameLogic()
	{
		int tempWin;
		cout<<"is real? in sub "<<whoTurn<<endl;
		privateList[whoTurn][stageIdx] = choiceWeapon;

		cout<<"turn info : "<<stageIdx<<" : " << whoTurn<<endl;
		cout<<privateList[0][stageIdx]<<" : " <<privateList[1][stageIdx]<<endl;
		// not ready for calc
		if(privateList[0][stageIdx] == -1 || privateList[1][stageIdx] == -1)
			return;

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

		cout<<"turn "<<stageIdx<<" : "<<endl;
		cout<<"p1 : "<<privateList[0][stageIdx]<<" vs "<<privateList[1][stageIdx]<<" : p2"<<endl;
		if(tempWin== -1) cout<<"draw!"<<endl;
		else cout<<"winner is "<<tempWin+1<<endl;

		if(tempWin != -1)
			winCount[tempWin]++;

		stageIdx++;
		stageInit();
		gameEndCheck();
	}

	void gameEndCheck()
	{
		if(abs(winCount[0] - winCount[1]) > stageNum - stageIdx)
			winner = winCount[0] > winCount[1] ? 1 : 2;
		else if(stageNum == stageIdx)
		{
			if(winCount[0] == winCount[1])
				winner = 0;
			else
				winner = winCount[0] > winCount[1] ? 1 : 2;
		}
	}

	// message's format is "turnCount,enemy's last weapon"
	string msgForToss()
	{
		char msg[50];
		if(stageIdx)
			snprintf(msg, sizeof(msg), "%d:%d", stageIdx, privateList[!whoTurn][stageIdx-1]);
		else
			snprintf(msg, sizeof(msg), "%d:%d", stageIdx, -1);
		return string(msg);
	}

	// this game's msg is only one char(0, 1, 2)
	// 0 : rock, 1 : scissor, 2 : paper
	virtual void parseForGet(vector<string> splittedMsg)
	{
		/*
		// normally use like this
		int len = splittedMsg.size();
		for(int i=0; i<len; i++)
			switch(i)
			{
			case 0 :
				break;
			case 1 :
				choiceWeapon = splittedMsg[1][0] - '0';
				break;
			}
		*/
		choiceWeapon = splittedMsg[1][0] - '0';
		isValidMsg();
	}

	void stageInit()
	{
		privateList[0][stageIdx] = -1;
		privateList[1][stageIdx] = -1;
	}

	virtual bool isValidMsg()
	{
		return true;
	}
};
