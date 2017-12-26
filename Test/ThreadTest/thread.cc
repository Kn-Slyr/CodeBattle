// g++ -std=c++11 -o ./exe/thread thread.cc -pthread
#include <iostream>
#include <thread>
#include <chrono>
#include <pthread.h>
using namespace std;

void uselessLoop();

int main(void)
{
	// thread *useless = new thread(uselessLoop);
	thread useless = thread(uselessLoop);

	cout<<"useless process is on...."<<endl;
	for(int i=0; i<5; i++)
	{
		this_thread::sleep_for(chrono::seconds(1));
		cout<<"wait for "<<i+1<<" sec..."<<endl;
	}
	pthread_cancel(useless);
	cout<<"useless process ends!"<<endl;


	return 0;
}

void uselessLoop()
{
	for(int i=0; i<10; i++)
	{
		cout<<i+1<<"th loop"<<endl;
		for(int j=0; j<500000000; j++);
	}
}
