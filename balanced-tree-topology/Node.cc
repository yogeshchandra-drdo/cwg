#include <omnetpp.h>
#include <string.h>
#include <iostream>
#include "Node.h"


void Node::initialize()
{
    //std::cout<<getName()<<"\n";

    if(strcmp(getName(),"0") == 0)
    {

    }

}
void Node::sendMessage()
{
    Enter_Method("sendMessage()");
    cMessage *left_msg = new cMessage("Multicast Frrom Root");
    send(left_msg,"left");
    cMessage *right_msg = left_msg->dup();
    send(right_msg,"right");
}
void Node::handleMessage(cMessage *msg)
{
        int flag=0;
        bubble("I received a multicast from root");
        if(this->gate("left")->isConnected())
        {
            cMessage *left_msg = msg->dup();
            send(left_msg,"left");
            flag=1;
        }
        if(this->gate("right")->isConnected())
        {
            cMessage *right_msg = msg->dup();
            send(right_msg,"right");
            flag=1;
        }
        /*if(gate("parent")->isConnected()){
            gate("parent")->getChannel()->callInitialize();
            send(msg,"parent");
        }*/

        if(flag==0)
        {
            bubble("Multicast ends here");
            delete msg;
        }
}
