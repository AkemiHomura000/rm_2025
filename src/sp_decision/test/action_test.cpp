
#include "node/observe_node.hpp"
#include <chrono>
#include <thread>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node_1 = std::make_shared<sp_decision::ActionNode>(1);
    node_1->set_action(1, "test_1", {1, 2, 3});
    auto node_2 = std::make_shared<sp_decision::ActionNode>(2);
    node_2->set_action(2, "test_2", {4, 5, 6});
    auto node_3 = std::make_shared<sp_decision::ActionNode>(3);
    node_3->set_action(3, "test_3", {7, 8, 9});

    auto sequence = std::make_shared<sp_decision::Sequence>(1);
    // sequence->add_action_node(*node_1);
    // sequence->add_action_node(*node_2);
    // sequence->add_action_node(*node_3);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    rclcpp::executors::MultiThreadedExecutor executor;

    // 添加节点到执行器
    executor.add_node(node_1);
    executor.add_node(node_2);
    executor.add_node(node_3);
    spdlog::info("tick squence node");
    sequence->tick_activate();
    sequence->tick_activate();
    sequence->tick_activate();
    // 让执行器同时 spin 这些节点
    executor.spin();

    rclcpp::shutdown();
    return 0;
}