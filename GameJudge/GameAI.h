#ifndef __GAME_AI_H__
#define __GAME_AI_H__

#include <iostream>
#include <string>
#include <pthread.h>	// for thread_create, detach
#include <thread>		// for this_thread::sleep_for
#include <chrono>		// for chrono::seconds
#include "NamedPipe.h"
// #include "TimeChecker.h"

using namespace std;

class GameAI
{
private :
	int usedTimeTotal;

protected :
	string gameName;
	string pipeMsg;
	int timeLimit;
	int myNumber;
	int turnCount;
	bool isFinishLogic;

	// TimeChecker *timeChecker;
	NamedPipe *pipe;

	int *privateList;		// privateList[idx]
	int **privateBoard;		// privateBoard[x][y]

public :
	GameAI(int playerNum)
	{
		cout<<"\tLoad GameAI...\n"<<endl;

		myNumber = playerNum;
		pipe = new NamedPipe(playerNum, false);

		readyToPlay();
	}

	~GameAI()
	{
		cout<<"\tClose GameAI...\n"<<endl;
		delete pipe;
		// delete timeChecker;
	}

	void playAI()
	{
		zeroTurnPlay();
		while(oneTurnProcess());
	}

private :
	// setup basic gameinfo
	virtual void setGameInfo() = 0;

	// toss message to judge for ready
	void readyToPlay()
	{
		string msg = "AI numberX on ready...";
		msg[9] = '0' + myNumber;
		pipe->toss(msg);
	}

	// alloc, free memory in privateList or privateBoard
	virtual void allocMemory() = 0;
	virtual void flushMemory() = 0;

	// setup timelimit
	virtual void setTimeChecker() = 0;

	// get message from GameJudge
	// set initial info of game
	virtual void zeroTurnPlay() = 0;

	// valid check for user's choice
	virtual bool isValidChoice() = 0;

	// get message from GameJudge(if get game end message, return false)
	// execute oneTurnPlay() = user's play
	// toss message to GameJudge and return true
	bool oneTurnProcess()
	{
		cout<<"\tPlayer"<<myNumber<<"\'s turn!"<<endl;
		// get message part
		pipe->getMsg(pipeMsg);
		if(hasGameEndSign())
		 	return false;
		parseForGet();

		// start threading for time limit check
		isFinishLogic = false;
		pthread_t oneThread;

		pthread_create(&oneThread, NULL, &GameAI::oneTurnPlay_wrapper, this);
		pthread_detach(oneThread);
		for(int i=0; i<timeLimit; i++)
		{
			this_thread::sleep_for(chrono::seconds(1));
			if(isFinishLogic) break;
		}

		// if too late to finish or user's return is invalid
		if(!isFinishLogic || !isValidChoice())
		{
			pthread_cancel(oneThread);
			pipeMsg = "OVER";
			pipe->toss(pipeMsg);
			return false;
		}

		parseForToss();
		pipe->toss(pipeMsg);
		return true;
	}

	// parse pipeMsg to get info
	// execute user's ai(analyze message, what to do)
	// parse play info at pipeMsg for toss message
	virtual void oneTurnPlay() = 0;

	static void* oneTurnPlay_wrapper(void* object)
	{
		reinterpret_cast<GameAI*>(object)->oneTurnPlay();
		return 0;
	}

protected :
	bool hasGameEndSign()
	{
		return pipeMsg.find("END") == 0;
	}

	// set pipeMsg by values in AIForXXX.cc
	virtual void parseForToss() = 0;
	// set values in AIForXXX.cc by pipeMsg
	// if message has game end signal return false, else true
	virtual void parseForGet() = 0;

	// add ai's think time total
	void usedTimeUpdate(int ms)
	{
		usedTimeTotal += ms;
	}
};

#endif
