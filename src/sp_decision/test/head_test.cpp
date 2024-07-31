#include "node/behavior_tree.hpp"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto tree=std::make_shared<sp_decision::BehaviorTree>();
    tree->behavior_tree_run_();
    // rclcpp::spin(tree);
    rclcpp::shutdown();
    return 0;
}