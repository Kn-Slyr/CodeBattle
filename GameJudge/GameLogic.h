#ifndef __GAME_LOGIC_H__
#define __GAME_LOGIC_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include "NamedPipe.h"
#include "MacroForPlay.h"

#define RANDOM 2

class GameLogic
{
protected :
	string gameName;

	int **privateList;		// privateList[player][idx]
	int *commonList;		// commonList[idx]
	int ***privateBoard;	// privateBoard[player][x][y]
	int **commonBoard;		// commonBoard[x][y]

	bool isAI[2];
	int playerNum;
	NamedPipe *pipe[2];
	vector<string> splittedMsg;

	int doFirst;
	int whoTurn;
	int winner;
	bool isGameEnd;

public :
	GameLogic(bool isAI1, bool isAI2)
	{
		cout<<"Load GameLogic..."<<endl;
		playerNum = 2;	// for extend to many player
		isAI[0] = isAI1;
		isAI[1] = isAI2;

		for(int player=PLAYER0; player<playerNum; player++)
			if(isAI[player])
			{
				string tmp;
				NamedPipe::makeFifoFile(player);
				pipe[player] = new NamedPipe(player, true);
				pipe[player]->getMsg(tmp);	// wait for AI load
				cout<<"AI"<<player+1<<" is ready!"<<endl;
			}

		setDoFirst();
	}

	~GameLogic()
	{
		printf("Close GameLogic...");

		for(int player=PLAYER0; player<playerNum; player++)
			if(isAI[player])
				delete pipe[player];
	}

	int gamePlay()
	{
		winner = -1;
		isGameEnd = false;
		zeroTurnPlay();

		while(winner == -1)
		{
			for(int i = 0, whoTurn = doFirst; i < 2; i++, whoTurn = !whoTurn)
			{
				cout<<"player "<<whoTurn<<"\'s turn!"<<endl;
				messageToPlayer();
				cout<<"is real? in super "<<whoTurn<<endl;
				playGameLogic();

				if(isGameEnd)
					break;
			}
		}
		return winner;
	}

private :
	// initiate basic game data
	virtual void setGameInfo() = 0;

	// set who will player first
	void setDoFirst(int first = RANDOM)
	{
		if(first == RANDOM)
		{
			int p0rand = -1, p1rand = -1;
			while(p0rand != p1rand)
			{
				p0rand = rand()%100;
				p1rand = rand()%100;
			}

			doFirst = p0rand < p1rand ? PLAYER1 : PLAYER0;
		}
		else
			doFirst = first;
	}

	// allocate memory at ***list or ***board
	virtual void allocMemory() = 0;

	// free memory for allocated in upper function
	virtual void flushMemory() = 0;

	// transfer initial information to players
	virtual void zeroTurnPlay() = 0;

	// one turn for player of "whoTurn"
	void messageToPlayer()
	{
		if(isAI[whoTurn])
			tossMsg();

		if(isAI[whoTurn])
			getMsg();
	}

	void tossMsg()
	{
		string pipeMsg = msgForToss();
		pipe[whoTurn]->toss(pipeMsg);
	}

	void getMsg()
	{
		pipe[whoTurn]->getSplittedMsg(splittedMsg, ':');
		parseForGet(splittedMsg);
		// if(splittedMsg[0][0] == CODE)
	}

	// check for game end
	// return : true for stage end, false for continue
	virtual void playGameLogic() = 0;

	// make string by child class's data & return it
	virtual string msgForToss() = 0;

	// fill vector with parsed message
	virtual void parseForGet(vector<string> splittedMsg) = 0;

	// check message is vaild
	virtual bool isValidMsg() = 0;
};

#endif
