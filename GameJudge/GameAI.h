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
protected :
	string gameName;
	string pipeMsg;
	int timeLimit;
	int myNumber;
	int turnCount;

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

	// get message from GameJudge(if get game end message, return false)
	// execute oneTurnPlay() = user's play
	// toss message to GameJudge and return true
	bool oneTurnProcess()
	{
		// get message part
		pipe->getMsg(pipeMsg);
		if(pipeMsg.find("END") == 0)		// game set
			return false;

		// start threading for time limit check
		// bool isClear = timeChecker->playThread(oneTurnPlay);
		int isEnd = 0;
		pthread_t oneThread;

		pthread_create(&oneThread, NULL, &GameAI::oneTurnPlay_wrapper, this);
		pthread_detach(oneThread);
		for(int i=0; i<timeLimit; i++)
		{
			this_thread::sleep_for(chrono::seconds(1));
			if(isEnd > 1) break;
		}

		if(!isEnd)
		{
			pthread_cancel(oneThread);
			pipeMsg = "OVER";
			pipe->toss(pipeMsg);
			return false;
		}

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
};

#endif
