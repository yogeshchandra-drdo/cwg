#include <omnetpp.h>
#include <string.h>
#include <iostream>
#include <ccomponenttype.h>
#include <cgate.h>
#include <cDelayChannel.h>
#include <carray.h>
#include <bits/stdc++.h>
#include <sys/types.h>
#include <unistd.h>
#include <cenvir.h>
#include <time.h>
#include <windows.h>
#include <time.h>
#include "Node.h"

class Tree : public cSimpleModule

{
  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    cDelayChannel *treeChannel1;
    cDelayChannel *treeChannel2;
    cDelayChannel *treeChannel3;
  private:
    void insert_Node();
    void delete_Node();
    void multicast_Node();
    void build_tree();
    int total_num;
    std::vector<cModule*> arr;
    std::vector<int>left_array;
    std::vector<int>right_array;
    std::vector<int>parent_array;
    std::vector<int>height_array;

};

Define_Module(Tree);
Define_Module(Node);
void Tree::initialize()
{
		
        std::cout<<"Initializing delay channel\n";
        
        std::cout<<"Initializing the Network\n";
        total_num = par("node_num");
        for(int i=0;i<total_num;i++)
        {
                cModuleType *modType = cModuleType::get("network_ass.Node");
                char buffer[10];itoa(i,buffer,10);
                arr.push_back(modType->create(buffer,this));
                arr[i]->finalizeParameters();
                left_array.push_back(-1);
                right_array.push_back(-1);
                parent_array.push_back(-1);
                height_array.push_back(1);
        }
        std::cout<<total_num<<"\n";
        
        build_tree();
        for(int i=0;i<total_num;i++)
        {
            arr[i]->buildInside();


        }
        std::cout<<"Array of Nodes intialised\n";
        srand(time(NULL));
        scheduleAt(simTime(),new cMessage);
    }


void Tree::handleMessage(cMessage *msg)
{

           int x = rand()%10000;
           //std::cout<<"Choice is : "<<x<<"\n";
           if(x<3333)
               x = 1;
           else if(x<6666)
               x = 2;
           else
               x = 3;
           std::cout<<"Choice is : "<<x<<"\n";
           switch(x)
           {
               case 1:
                   sleep(1);
                   insert_Node();
                   break;
               case 2:
                   sleep(1);
                   delete_Node();
                   break;
               case 3:
                   multicast_Node();
                   break;
           }
           //sleep(3);
           scheduleAt(simTime()+5000,msg);
}

void Tree::build_tree()
{

    for(int i=0;i<(total_num)/2;i++)
    {
        char buffer[10];
        itoa(i,buffer,10);
        cGate *leftGate = arr[i]->gate("left");
        cGate *rightGate = arr[i]->gate("right");
        if(2*i+1 < total_num)
        {
            if(!leftGate->isConnected()){
                leftGate->connectTo(arr[2*i+1]->gate("parent"));

            }
            left_array[i] = 2*i+1;
            parent_array[2*i+1] = i;
        }

        if(2*i+2 < total_num)
        {
            if(!rightGate->isConnected()){
                rightGate->connectTo(arr[2*i+2]->gate("parent"));

            }
            right_array[i] = 2*i+2;
            parent_array[2*i+2] = i;
        }
        if(2*i+1<total_num && parent_array[2*i+1] !=-1)
        {
            height_array[2*i+1] = height_array[parent_array[2*i+1]]+1;
            std::cout<<"Height : "<<2*i+1<<" :  "<<height_array[2*i+1]<<"\n";
        }
        if(2*i+2<total_num && parent_array[2*i+2] !=-1)
        {
            height_array[2*i+2] = height_array[parent_array[2*i+2]]+1;
            std::cout<<"Height : "<<2*i+2<<" :  "<<height_array[2*i+2]<<"\n";
        }

    }
}

void Tree::insert_Node()
{
    if(total_num>=100)
        return;
    total_num++;
    cModuleType *modType = cModuleType::get("network_ass.Node");
    char buffer[10];itoa(total_num-1,buffer,10);
    arr.push_back(modType->create(buffer,this));
    arr[total_num-1]->finalizeParameters();
    left_array.push_back(-1);
    right_array.push_back(-1);
    parent_array.push_back(-1);
    height_array.push_back(1);
    int parent = (int)floor((total_num/2)-1);
    cGate *leftGate = arr[parent]->gate("left");
    cGate *rightGate = arr[parent]->gate("right");
    cGate *parentGate  = arr[total_num-1]->gate("parent");
    if(2*parent+1 <total_num && total_num%2==0)
    {
        leftGate->connectTo(parentGate);
        left_array[parent]=total_num-1;

    }
    if(2*parent+2 <total_num && total_num%2!=0)
    {
        rightGate->connectTo(parentGate);
        right_array[parent]=total_num-1;
    }
    parent_array[total_num-1]=parent;
    height_array[total_num-1]=height_array[parent]+1;
    std::cout<<"Height : "<<total_num-1<<" :  "<<height_array[total_num-1]<<"\n";
    arr[total_num-1]->buildInside();
    arr[total_num-1]->callInitialize();
}
void Tree::delete_Node()
{
    if(total_num<=10)
            return;
    int index = rand()%total_num;
    std::cout<<"Deleting node at index : "<<index<<"\n";
    if(index < total_num && index>=0)
    {
        arr[index]->deleteModule();
        //delete arr[index];
        total_num--;
        arr.erase (arr.begin()+index);
        for(int i=0;i<total_num;i++)
        {
            arr[i]->gate("left")->disconnect();
            arr[i]->gate("right")->disconnect();
        }
        build_tree();
    }
    else
        std::cout<<"Please Enter a valid index\n";

}
void Tree::multicast_Node()
{
    std::cout<<"Starting Multicast\n";
    ((Node *)arr[0])->sendMessage();
}
