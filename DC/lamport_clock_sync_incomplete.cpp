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
#define NUMBER_OF_THREADS 5
vector<int> sharedresourceA;
bool resourceLock= false;
vector<int> earlier_time;
bool isMessage(int i)
{
    if(earlier_time[i]!=sharedresourceA[i])
    {
        return true;
    }
    else
    {
        return false;
    }
}
void process_t(int i)
{
    int clock=0;
    while(true)
    {
        if(isMessage(i))
        {
            if(earlier_time[i]<sharedresourceA[i])
             {
                 clock=sharedresourceA[i]+1;
                 cout<<"clock updated. earlier time:"<<earlier_time[i]<<"\t new time:"<<clock<<"\n";
                 earlier_time[i]=clock;
             }
             else
             {
                 cout<<"message recieved\n";
                 clock++;
             }
        }else
        {
            clock++;
        }
        if(!resourceLock)
         {
             resourceLock=true;
             int s=rand() % NUMBER_OF_THREADS + 1;
             sharedresourceA[s]=clock;
             resourceLock = false;
         }
    }
}

int main()
{
    thread g[NUMBER_OF_THREADS];
    for( int i=0; i<NUMBER_OF_THREADS;i++)
    {
        g[i](process_t(i));
    }
}
