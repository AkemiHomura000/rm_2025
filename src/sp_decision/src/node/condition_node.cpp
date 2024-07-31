#include "node/condition_node.hpp"

namespace sp_decision
{
    HeadNode::HeadNode() : Node("head_node")
    {
        blackboard_ = std::make_shared<BlackBoard>();
        pub_node_ = std::make_shared<PubNode>();
    }

    HeadNode::~HeadNode()
    {
        if (decision_thread_.joinable())
        {
            decision_thread_running_ = false;
            decision_thread_.join();
        }
        spdlog::info("head_node has been destroyed.");
    }
    void HeadNode::head_init(std::shared_ptr<sp_decision::ConditionNode> condition_node)
    {
        condition_node_ = condition_node;
    }

    void HeadNode::run()
    {
        rclcpp::Rate loop_rate(LOOP_FREQUENCY);
        while (decision_thread_running_)
        {
            tick_activate();
            loop_rate.sleep();
        }
    }
    void HeadNode::start_judge()
    {
        decision_thread_running_ = true;
        decision_thread_ = std::thread(&HeadNode::run, this);
    }

    void HeadNode::kill_thread()
    {
        if (decision_thread_.joinable())
        {
            decision_thread_running_ = false;
            decision_thread_.join();
        }
    }

    void HeadNode::tick_activate()
    {
        // std::this_thread::sleep_for(std::chrono::seconds(1));
        num++;
        spdlog::info("head_node is activated {} times.", num);
        condition_node_->tick_activate();
    }
    void HeadNode::tick_deactivate()
    {
        spdlog::info("HeadNode tick_deactivate");
    }
    void HeadNode::update(ActionState state)
    {
        spdlog::info("HeadNode update");
    }
    PubNode::PubNode() : Node("pub_node")
    {
        spdlog::info("PubNode is created");
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    }
    PubNode::~PubNode()
    {
        spdlog::info("PubNode is destroyed");
    }
    void PubNode::publish_state(int node_id)
    {
        // 创建一个消息并填充数据
        auto message = std_msgs::msg::String();
        message.data = "Hello, ROS 2!  " + std::to_string(node_id);
        // 发布消息
        publisher_->publish(message);
    }

    // 判定函数0：返回true，确保动作节点下一个一定是左节点
    bool compare_0(double a, double b)
    {
        return true;
    }
    // 判定函数1：决策变量>条件量
    bool compare_1(double a, double b)
    {
        return (a > b) ? 1 : 0;
    }
    // 判定函数2：决策变量<条件量
    bool compare_2(double a, double b)
    {
        return (a < b) ? 1 : 0;
    }
    // 判定函数3：决策变量==条件量
    bool compare_3(double a, double b)
    {
        return (a == b) ? 1 : 0;
    }
    // 判定函数4：决策变量!=条件量
    bool compare_4(double a, double b)
    {
        return (a != b) ? 1 : 0;
    }
    sp_decision::ConditionNode::ConditionNode(int id)
    {
        node_id_ = id;
        left_node_ = nullptr;
        right_node_ = nullptr;
        left_observer_ = nullptr;
        right_observer_ = nullptr;
    }
    ConditionNode::~ConditionNode()
    {
        head_node_->kill_thread();
        spdlog::info("Condition node_{} has been destroyed.", node_id_);
    }
    void ConditionNode::init(std::shared_ptr<sp_decision::HeadNode> head_node)
    {
        head_node_ = head_node;
        pub_node_ = head_node_->pub_node_;
        blackboard_ = head_node_->blackboard_;
    }
    void ConditionNode::set_condition(std::string variable_name, double condition_value, CompareFunction compare_function)
    {
        variable_name_ = variable_name;
        condition_value_ = condition_value;
        compare_function_ = compare_function;
    }
    void ConditionNode::connect(ConditionNode *left, ConditionNode *right)
    {
        left_node_ = left;
        right_node_ = right;
    }

    void ConditionNode::connect_observer(Observer *left_observer, Observer *right_observer)
    {
        if (left_observer != nullptr)
            left_observer_ = left_observer;
        if (right_observer != nullptr)
            right_observer_ = right_observer;
    }
    bool ConditionNode::node_judge()
    {
        pub_node_->publish_state(node_id_);
        if (blackboard_->check_key(variable_name_))
        {
            spdlog::info("judge {}", node_id_);
            bool result = compare_function_(blackboard_->get_value(variable_name_), condition_value_);
            spdlog::info("Variable {} is found, the result is {}", variable_name_, result);
            return result;
        }
        else
        {
            spdlog::info("Variable {} is not found", variable_name_);
            return false;
        }
        return false;
    }
    void ConditionNode::tick_activate()
    {
        spdlog::info("condition node ticked");
        if (node_judge())
        {
            if (left_node_ != nullptr)
                left_node_->tick_activate();
            else if (left_observer_ != nullptr)
                left_observer_->tick_activate();
            else
                return;
        }
        else
        {
            if (right_node_ != nullptr)
                right_node_->tick_activate();
            else if (right_observer_ != nullptr)
                right_observer_->tick_activate();
            else
                return;
        }
    }
    void ConditionNode::tick_deactivate()
    {
        if (!node_judge())
        {
            left_node_->tick_activate();
        }
        else
        {
            right_node_->tick_activate();
        }
    }
    void ConditionNode::update(ActionState state)
    {
        spdlog::info("Condition node_{} is updated.", node_id_);
    }
}
