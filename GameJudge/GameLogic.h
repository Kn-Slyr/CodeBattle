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

private :
	bool isAI[2];
	int playerNum;
	NamedPipe *pipe[2];
	vector<string> splittedMsg;

	int doFirst;
	int whoTurn;
	int winner;
	int turnCount;
	bool isGameEnd;

// getter & setter for subclass(GameLogicForXXX.cc)
protected :
	int getWhoTurn() const { return whoTurn; }
	int getPlayerNum() const { return playerNum; }
	int getTurnCount() const { return turnCount; }
	vector<string> const &getSplittedMsg() const { return splittedMsg; }

	void setWinner(int _winner) { winner = _winner; }

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
				cout<<"AI"<<player<<"\'s pipe is ready!"<<endl;
			}

		setWhoPlayFirst();
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
		turnCount = -1;
		isGameEnd = false;

		whoTurn = doFirst;
		for(int i = 0; i < 2; i++, whoTurn = !whoTurn)
		{
			zeroTurnPlay();
			tossMsg();
		}

		turnCount = 0;
		while(winner == -1)
		{
			turnInit();
			whoTurn = doFirst;
			cout<<"turn count : "<<turnCount<<endl;
			for(int i = 0; i < 2; i++)
			{
				whoTurn = !whoTurn;
				cout<<"  player "<<whoTurn<<"\'s turn!"<<endl;
				if(isAI[whoTurn])
				{
					tossMsg();
					getMsg();
				}
				else
				{
					// for user interface
				}

				playGameLogic();

				if(isGameEnd)
					break;
			}
			turnCount++;
		}
		return winner;
	}

private :
	// set who will player first, it just for 2 players
	void setWhoPlayFirst(int first = RANDOM)
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

	// set msg with game info
	// then, toss msg to AI of 'whoTurn'
	void tossMsg()
	{
		string pipeMsg = makeMsgForToss();
		pipe[whoTurn]->toss(pipeMsg);
	}

	// get msg from AI of 'whoTurn'
	// then, parse msg to game info
	void getMsg()
	{
		pipe[whoTurn]->getSplittedMsg(splittedMsg, ':');
		parseForGet();
	}

// specific for each games
private :
	// initiate basic game data
	virtual void setGameInfo() = 0;

	// allocate memory at ***list or ***board
	virtual void allocMemory() = 0;

	// free memory for allocated in upper function
	virtual void flushMemory() = 0;

	// transfer initial information to players
	virtual void zeroTurnPlay() = 0;

	// check for game end
	// return : true for stage end, false for continue
	virtual void playGameLogic() = 0;

	// make string by child class's data & return it
	virtual string makeMsgForToss() = 0;

	// fill vector with parsed message
	virtual void parseForGet() = 0;

	// if have to set something for every turn, use this function
	virtual void turnInit() = 0;

	// check message is vaild
	virtual bool isValidMsg() = 0;

	// check for is winner come
	virtual bool checkGameEnd() = 0;
};

#endif
