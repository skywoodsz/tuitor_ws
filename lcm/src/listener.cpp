#include<lcm/lcm-cpp.hpp>
#include"exlcm/example_t.hpp"
#include<stdio.h>
#include<iostream>

class Handle
{
    public:
        ~Handle(){}
        
        void handleMessage(const lcm::ReceiveBuffer* rbuf, const std::string& chan,  const exlcm::example_t* msg)
        {
            int i;
            printf("Received message on channel \"%s\":\n", chan.c_str());
            printf("  timestamp   = %lld\n", (long long)msg->timestamp);
            printf("  position    = (%f, %f, %f)\n",
                    msg->position[0], msg->position[1], msg->position[2]);
            printf("  orientation = (%f, %f, %f, %f)\n",
                    msg->orientation[0], msg->orientation[1], 
                    msg->orientation[2], msg->orientation[3]);
            printf("  ranges:");
            for(i = 0; i < msg->num_ranges; i++)
                printf(" %d", msg->ranges[i]);
            printf("\n");
            printf("  name        = '%s'\n", msg->name.c_str());
            printf("  enabled     = %d\n", msg->enabled);
        }

};


int main()
{
    lcm::LCM lcm;
    if(!lcm.good())
    {
        std::cout<<"lcm init fail!"<<std::endl;
        return 1;
    }
    
    Handle handlerObject;
    lcm.subscribe("EXAMPLE", &Handle::handleMessage, &handlerObject);
    
    while(lcm.handle() == 0)
    {
        std::cout<<"lcm.handle(): "<<lcm.handle()<<std::endl;
    }
        
    return 0;
}
