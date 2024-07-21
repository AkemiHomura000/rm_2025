#include "node/node.hpp"
#include "tools/logger.hpp"
#include <vector>
#include <thread>
using namespace sp_decision;
int judge(MyNode *node)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 间隔50ms
    spdlog::info("Node {} is judged", node->node_id);
    bool sys = node->node_judge();
    if (sys)
    {
        if (node->left_node != nullptr)
        {

            spdlog::info("1");
            return judge(node->left_node);
        }
        return 0;
    }
    else
    {
        if (node->right_node != nullptr)
        {
            spdlog::info("2");
            return judge(node->right_node);
        }
        return 0;
    }
}
int main(int argc, char **argv)
{
    std::vector<MyNode *> nodes;
    for (int i = 0; i < 10; i++)
    {
        MyNode *new_node = new MyNode(i);
        nodes.push_back(new_node);
        spdlog::info("Node {} is created", new_node->node_id);
        if (i > 0)
        {
            nodes[i - 1]->left_node = new_node;
            nodes[i - 1]->right_node = new_node;
        }
    }
    while (1)
    {
        judge(nodes[0]);
    }
    return 0;
}