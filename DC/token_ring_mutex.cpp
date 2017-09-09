#include <iostream>
#include <vector>
#include <cstdlib>
#include <thread>
#define NUMBER_OF_THREADS 5
/*
*	token ring :
*	machines emulated as threads. independent of each other
*	one struct as critical resource. 
*	random bool value generator to emulate random need of resource.
*	the need for resource changes after passing on the token to the next machine.
*/
struct resource		//critical resource struct
{
	bool lock;
	int res;
};
bool getBool()		//random boolean value generator
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
struct resource r1;				//single critical resource
int passto;						//token to be passed among machines
void proc(int procid)
{
	bool needResource = getBool();
	while (true)
	{
		if (procid == passto)
		{
			std::cout << "\ntoken acquired by machine"<<procid<<std::endl;
			if (needResource)
			{
				r1.lock = true;
				std::cout << "machine"<<procid<<" is using the resource"<<std::endl;
				r1.res = rand() % 10;
				_sleep(1500);			
				std::cout << "machine" << procid << " has finished using the resource" << std::endl;
				r1.lock = false;
				needResource = getBool();
			}
			else
			{
				std::cout << "machine" << procid << " does not need the resource" << std::endl;	
				needResource = getBool();
			}
			if (++passto < NUMBER_OF_THREADS)
			{
				std::cout << "token passed from machine" << procid << " to machine" << passto << "  " << std::endl;
			}
			else
			{
				passto = 0;
				std::cout << "token passed from machine" << procid << " to machine" << passto<<"  " << std::endl;
			}
		}
		else
		{
			if (needResource) {
				_sleep(1000);
				std::cout << "machine" << procid << " is waiting for the resource. " << std::endl;
			}
		}
	}
}
int main()
{
	passto = 0;
	std::thread mythread[NUMBER_OF_THREADS];
	std::vector<std::thread> mythreads;
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		mythreads.push_back(std::thread(proc, i));	//starting threads
	}
	/*
	*		The program will not go beyond this point as threads are in infinite while loop.
	*/
	for (int i = 0; i < NUMBER_OF_THREADS; i++)
	{
		mythreads[i].join();	//closing of threads
	}
	return 0;
}
