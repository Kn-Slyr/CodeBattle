// g++ -std=c++11 -o ./exe/thread thread2.cc -pthread
#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>

#define LOOPNUM 20
#define WAITSEC 3

using namespace std;


void *uselessLoop(void *pArg);

int main(int argc, char **argv)
{
	int ret = -1;
	pthread_t useless;

	pthread_create(&useless, NULL, uselessLoop, (void*)&ret);
	pthread_detach(useless);	// is this need?
	cout<<"useless process is on...."<<endl;
	for(int i=0; i<WAITSEC; i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
		cout<<"wait for "<<i+1<<" sec..."<<endl;
		if(ret == 1)
		{
			cout<<"thread end, wait finish"<<endl;
			break;
		}
	}

	if(ret == 1)
	{
		cout<<"thread successfully end!"<<endl;
	}
	else if(ret == -1)
	{
		cout<<"thread not end, cacnel it"<<endl;
		pthread_cancel(useless);
	}

	return 0;
}

void *uselessLoop(void *pArg)
{
	int *ret = (int*)pArg;
	for(int i=0; i<LOOPNUM; i++)
	{
		cout<<i+1<<"th loop"<<endl;
		for(int j=0; j<100000000; j++);
	}
	*ret = 1;
}
