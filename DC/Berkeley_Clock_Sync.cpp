#include <iostream>
#include <thread>
#include <vector>
#include <cstdlib>
#define NUMBER_OF_THREADS 3
/*
*      two/n slave process. one coordinator process.
*
*
*
*
*
*/
std::vector<float> timeUpdate;
std::vector<float> getTime;
bool askTime=false,updateTime=false;
void process_slave(int i,int t)
{
    float time= 0.0;
    bool pastUpdate=false;
	while(true)
    {
        time =time+1.0;
        if(askTime)
        {
            getTime[i]=time;
        }

        if(pastUpdate!=updateTime)
        {
            time=time+timeUpdate[i];
            pastUpdate=updateTime;
        }
       // _sleep(100);
    }
}
bool getBool()
{
    srand(time(NULL));
	int randomNumber = rand() % 100 + 1;
	if (randomNumber % 2 == 0)
	{
		return true;
	}
	else {
		return false;
	}
}
void process_master()
{
    float time =0.0;float sum=0.0,avg=0.0;
    while(true)
    {
        time = time +1.0;
        if(getBool())
        {
            askTime=true;
          //  _sleep(250);
            for(int i=0;i<NUMBER_OF_THREADS;i++)
            {
                sum =sum+ (time-getTime[i]);
            }
            avg=sum/NUMBER_OF_THREADS;
            for(int i=0;i<NUMBER_OF_THREADS;i++)
            {
                timeUpdate[i]=avg-getTime[i];
            }
            updateTime= !updateTime;
        }
        askTime=false;
    }
}

int main()
{
	std::vector<std::thread> myThreads;
	for(int i=0;i<NUMBER_OF_THREADS;i++)
    {
        myThreads.push_back(std::thread (process_slave,i,(1000/i)));
    }
    std::thread pp(process_slave);
    for(int i=0;i<NUMBER_OF_THREADS;i++)
    {
        myThreads[i].join();
    }
    pp.join();
}
