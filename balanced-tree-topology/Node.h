#pragma once
class Node : public cSimpleModule
{
    public:
        int left_child ;
        int parent_point;
        int right_child;
        int height;
        void sendMessage();
     protected:
        virtual void initialize();
        virtual void handleMessage(cMessage *msg);

};
Define_Module(Node);
