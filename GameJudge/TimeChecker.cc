#include "TimeChecker.h"

TimeChecker::TimeChecker(int _timeLimit)
{
	timeLimit = _timeLimit;
}

bool TimeChecker::playThread(void* (GameAI::*aiThinkFunction)(void* pArgv))
{
	int isEnd = 0, timeCounter;
	pthread_create(&oneThread, NULL, aiThinkFunction, (void*)&isEnd);
	pthread_detach(oneThread);
	for(int timeCounter=0; timeCounter<timeLimit; timeCounter++)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if(isEnd) break;
	}

	// @@todo hacker check
	// if(timeCounter*1000 < isEnd)
	// 	return false;

	// successfully finish ai logic
	if(isEnd)
		return true;

	pthread_cancel(oneThread);
	return false;
}
