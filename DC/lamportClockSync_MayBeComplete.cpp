/*
*   use threads to represent different machines.
*   An iterator to signify clock.
*   make threads communicate with each other.
*   A thread will send a message and a timestamp of its clock to another thread.
*   Might have to use shared resource.
*
*/

#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
using namespace std;
#define NUMBER_OF_THREADS 2
vector<int> sharedresourceA;
bool resourceLock = false;
vector<int> earlier_time;
bool isMessage(int i)
{
	if (earlier_time[i] != sharedresourceA[i])
	{
		return true;
	}
	else
	{
		return false;
	}
}
void process_t(int i,int t)
{
	int clock = 0;
	
	while (true)
	{
		if (isMessage(i))
		{
			if (earlier_time[i]<sharedresourceA[i])
			{
				clock = sharedresourceA[i] + 1;
				cout << "\nmessage recieved by Machine" << i <<"\nclock updated. earlier time:" << earlier_time[i] <<"time read:"<<sharedresourceA[i]<< "\t new time:" << clock <<endl;
				earlier_time[i] = clock;
			}
			else
			{
				cout << "\nclock of Machine"<<i<<" in sync. Clock Time:"<<clock<<endl;
				earlier_time[i]= ++clock;
			}
		}
		else
		{
			cout << "\nMachine"<<i<<" waiting for message. Clock Time: "<<clock<<endl;
			earlier_time[i]= ++clock;
		}
		if (!resourceLock)
		{
			int s = rand() % NUMBER_OF_THREADS + 1;
			if (s != i)
			{
				resourceLock = true;
				sharedresourceA[s] = clock;
				resourceLock = false;
				cout << "message sent by Machine" << i << endl;
			}
		}
		_sleep(t);
	}
}

int main()
{
	earlier_time.push_back(0);
	sharedresourceA.push_back(0);
	earlier_time.push_back(0);
	sharedresourceA.push_back(0);
	earlier_time.push_back(0);
	sharedresourceA.push_back(0);
	cout << "clock interval of machine 1 : 1000ms \nclock interval of machine 2: 900ms" << endl;
	thread t1(process_t, 1,1000);
	thread t2(process_t, 2,900);
	
	t1.join();
	t2.join();
}
