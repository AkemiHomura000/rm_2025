#ifndef NODE
#define NODE
#include <iostream>
#include <random>
#include "tools/logger.hpp"
namespace sp_decision
{
    class MyNode
    {
    public:
        int node_id;
        MyNode(int id);
        ~MyNode();
        void connect(MyNode *left, MyNode *right);
        MyNode *left_node;
        MyNode *right_node;
        bool node_judge();
    private:
    };
}
#endif