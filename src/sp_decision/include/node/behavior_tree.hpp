#include "node/condition_node.hpp"
#include "node/observe_node.hpp"
#include <yaml-cpp/yaml.h>
#include <ament_index_cpp/get_package_prefix.hpp>
#include <ament_index_cpp/get_package_share_directory.hpp>

namespace sp_decision
{
    class BehaviorTree
    {
    public:
        BehaviorTree();
        ~BehaviorTree();
        void behavior_tree_init_();
        void behavior_tree_run_();
        ConditionNode *get_condition_node(int id);
        std::shared_ptr<ActionNode> get_action_node(int id);

    private:
        std::shared_ptr<sp_decision::HeadNode> head_node_;
        std::vector<std::shared_ptr<sp_decision::ConditionNode>> condition_nodes_;
        std::vector<std::shared_ptr<sp_decision::Observer>> observer_nodes_;
        std::vector<std::shared_ptr<sp_decision::ActionNode>> action_nodes_;
    };

}