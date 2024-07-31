#include <chrono>
#include <thread>
#include "node/condition_node.hpp"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto blackboard = std::make_shared<sp_decision::BlackBoard>();
    blackboard->set_value("test_1", 1);
    blackboard->set_value("test_2", 2);
    blackboard->set_value("test_3", 3);
    blackboard->set_value("test_4", 4);

    // auto pub_node = std::make_shared<sp_decision::PubNode>();
    // auto node_1 = std::make_shared<sp_decision::ConditionNode>(1);
    // node_1->init(node_1, blackboard);
    // node_1->set_condition("test_1", 0, sp_decision::compare_0);
    // auto node_2 = std::make_shared<sp_decision::ConditionNode>(2);
    // node_2->init(node_1, blackboard);
    // node_2->set_condition("test_1", 2, sp_decision::compare_1);
    // auto node_3 = std::make_shared<sp_decision::ConditionNode>(3);
    // node_3->init(node_1, blackboard);
    // node_2->set_condition("test_2", 0, sp_decision::compare_2);
    // auto node_4 = std::make_shared<sp_decision::ConditionNode>(4);
    // node_4->init(node_1, blackboard);
    // node_2->set_condition("test_3", -1, sp_decision::compare_3);
    // auto node_5 = std::make_shared<sp_decision::ConditionNode>(5);
    // node_5->init(node_1, blackboard);
    // node_2->set_condition("test_4", 20, sp_decision::compare_4);

    // std::this_thread::sleep_for(std::chrono::seconds(1));

    // rclcpp::executors::MultiThreadedExecutor executor;
    // executor.add_node(blackboard);
    // spdlog::info("tick head node");
    // node_1->tick_activate();
    // // 让执行器同时 spin 这些节点
    // executor.spin();

    // rclcpp::shutdown();
    return 0;
}