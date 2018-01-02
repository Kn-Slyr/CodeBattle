#ifndef __TIME_CHECKER_H__
#define __TIME_CHECKER_H__

#include <pthread.h>
#include <thread>
#include <chrono>
#include "GameAI.h"

class TimeChecker
{
private :
	int timeLimit;
	pthread_t oneThread;

public :
	TimeChecker(int _timeLimit);
	bool playThread(void* ((GameAI::*aiThinkFunction)(void* pArgv)));
};

#endif
