#ifndef CONDITION_NODE
#define CONDITION_NODE
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <string>

#include "perception/blackboard.hpp"
#include "node/action_node.hpp"
#include "tools/logger.hpp"

constexpr int LOOP_FREQUENCY = 1;
namespace sp_decision
{
    class ConditionNode;
    class PubNode;
    class HeadNode : public rclcpp::Node, public Observer
    {
    public:
        HeadNode();
        ~HeadNode();
        void head_init(std::shared_ptr<sp_decision::ConditionNode> condition_node);
        void run();
        void start_judge();
        void kill_thread();
        void tick_activate() override;           // 激活
        void tick_deactivate() override;         // 关闭
        void update(ActionState state) override; // 被观察者调用

        std::shared_ptr<sp_decision::BlackBoard> blackboard_;
        std::shared_ptr<sp_decision::PubNode> pub_node_;

    private:
        int num = 0;
        std::thread decision_thread_;
        bool decision_thread_running_;
        std::shared_ptr<sp_decision::ConditionNode> condition_node_;
    };

    class PubNode : public rclcpp::Node
    {
    public:
        PubNode();
        ~PubNode();
        void publish_state(int node_id);
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    };


    using CompareFunction = bool (*)(double, double);
    bool compare_0(double a, double b);
    // 判定函数1：决策变量>条件量
    bool compare_1(double a, double b);
    // 判定函数2：决策变量<条件量
    bool compare_2(double a, double b);
    // 判定函数3：决策变量==条件量
    bool compare_3(double a, double b);
    // 判定函数4：决策变量!=条件量
    bool compare_4(double a, double b);
    class ConditionNode : public Observer
    {
    public:
        int node_id_;
        ConditionNode(int id);
        ~ConditionNode();
        void init(std::shared_ptr<sp_decision::HeadNode> head_node);
        void set_condition(std::string variable_name, double condition_value, CompareFunction compare_function);
        void connect(ConditionNode *left, ConditionNode *right);
        void connect_observer(Observer *left_observer,Observer *right_observer);
        bool node_judge();
        void publish_message(int node_id);

        void tick_activate() override;           // 激活
        void tick_deactivate() override;         // 关闭
        void update(ActionState state) override; // 被观察者调用


    private:
        std::string variable_name_;
        double condition_value_;
        CompareFunction compare_function_;
        ConditionNode *left_node_;
        ConditionNode *right_node_;
        Observer *left_observer_;
        Observer *right_observer_;
        std::shared_ptr<sp_decision::BlackBoard> blackboard_;
        std::shared_ptr<sp_decision::HeadNode> head_node_;
        std::shared_ptr<sp_decision::PubNode> pub_node_;
    };

}
#endif