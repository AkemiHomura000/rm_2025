#include "node/node.hpp"
namespace sp_decision
{
    MyNode::MyNode(int id)
    {
        node_id = id;
        left_node = nullptr;
        right_node = nullptr;
    }
    void MyNode::connect(MyNode *left, MyNode *right)
    {
        left_node = left;
        right_node = right;
    }
    int generate_random_number(int min, int max)
    {
        std::random_device rd;                         // 用于获得随机种子
        std::mt19937 gen(rd());                        // Mersenne Twister 引擎
        std::uniform_int_distribution<> dis(min, max); // 均匀分布
        return dis(gen);
    }
    bool MyNode::node_judge()
    {
        bool result = generate_random_number(0, 10) % 2;
        spdlog::info("Node {} is judged as {}", node_id, result);
        return result;
    }
    MyNode::~MyNode()
    {
        std::cout << "Node " << node_id << " is destroyed" << std::endl;
    }
}
