/*  
*      
*
*   multiple threads. 
*   each thread is a server. A single thread for load balancer. 
*   each server will give requests and will take tasks.
*   Two queues: one for queueing request and another for queueing load.
*   Loads are randomly generated and added to the queue by a separate thread. 
*   Requests are given by servers by adding the their id to queue. 
*   Central load balancer will check check both queues and thus allocating tasks
*   accordingly.
*
*/
#include <iostream>
#include <queue>
#include <cstdlib>
#include <pthread.h>
#define THRESHOLD 10
#define NUMBER_OF_PROCESSES 5
struct threadproperties
{
    int request,load,id;
    std::queue<int> *reqval;
};
struct loadbal
{
    std::queue<int> *reqval;
    struct threadproperties [NUMBER_OF_PROCESSES] *p;
};
void *server(void *s)
{
    int id;
    struct threadproperties *a=s;
    a.load=0;
    id=a.id;
    while(true)
    {
        if(a.load==0)
            reqval.push(id);

        if(a.load>0)
            a.load--;
    }
}
void *LoadBalancer(void *s)
{
    struct loadbal *a=s;
    std::queue<int> load;
    while(true)
    {
        load.push(rand % 10 +1);
        struct threadprope
    }
}

int main()
{
   
}
