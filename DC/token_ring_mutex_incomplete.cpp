#include <iostream>
#include <vector>
#include <cstdlib>

#define NUMBER_OF_THREADS 5
/*
*   token ring :
*   process as threads. independent of each other
*   one resource struct. 
*   
*
*/
struct resource
{
    bool lock;
    int res;
};
struct resource r1;
int passto;
void proc(int procid)
{
    int need= rand() % 5 + 4;
    while (true)
    {
        
        need =need -4;
        if(procid==passto)
        {
            std::cout<<"token acquired";
            if(need==1)
            {
                std::cout<<"resource required";
                _sleep(2000);
                 need= rand() % 5 + 4;
            }
            if(passto< NUMBER_OF_THREADS)
              {
                  passto++;
              } 
              else
                {
                passto =0;
              }
            
        }
        else{
            if(need==1)
            {
                std::cout<<"waiting for resource";
            }
            else
            {
                 need= rand() % 5 + 4;
            }
        }
       
    }
}
int main()
{
    
    
    return 0;
}
