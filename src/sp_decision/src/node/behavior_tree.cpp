#include "node/behavior_tree.hpp"

namespace sp_decision
{
    BehaviorTree::BehaviorTree()
    {
        head_node_ = std::make_shared<sp_decision::HeadNode>();
        head_node_->blackboard_->set_value("test1", 1);
        head_node_->blackboard_->set_value("test2", 10);
        behavior_tree_init_();
    }

    BehaviorTree::~BehaviorTree()
    {
        head_node_->kill_thread();
        spdlog::info("BehaviorTree has been destroyed.");
    }
    void BehaviorTree::behavior_tree_init_()
    {
        std::string filename = "tree.yaml";
        std::string package_name = "sp_decision";
        try
        {
            std::string package_prefix = ament_index_cpp::get_package_prefix(package_name);
            filename = package_prefix + "/../../src/sp_decision/config/test.yaml";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        spdlog::info("file path : {}", filename);
        YAML::Node config = YAML::LoadFile(filename);
        //---------------------------------------------------------------condition_node-------------------------------------------------
        for (const auto &node : config["decision_tree_1"])
        {
            if (node["node_type"].as<std::string>() == "condition")
            {
                auto condition_node = std::make_shared<ConditionNode>(node["id"].as<int>());
                condition_node->init(head_node_);
                if (node["condition"].as<std::string>() == ">")
                    condition_node->set_condition(node["variable"].as<std::string>(), node["condition_value"].as<double>(), sp_decision::compare_1);
                else if (node["condition"].as<std::string>() == "<")
                    condition_node->set_condition(node["variable"].as<std::string>(), node["condition_value"].as<double>(), sp_decision::compare_2);
                else if (node["condition"].as<std::string>() == "==")
                    condition_node->set_condition(node["variable"].as<std::string>(), node["condition_value"].as<double>(), sp_decision::compare_3);
                else if (node["condition"].as<std::string>() == "!=")
                    condition_node->set_condition(node["variable"].as<std::string>(), node["condition_value"].as<double>(), sp_decision::compare_4);
                condition_nodes_.push_back(condition_node);
                spdlog::info("condition node_{} created  ", condition_node->node_id_);
                if (condition_node->node_id_ == 1)
                    head_node_->head_init(condition_node);
            }
        }
        for (const auto &node : config["decision_tree_1"])
        {
            if (node["node_type"].as<std::string>() == "condition")
            {
                int node_id = (node["id"].as<int>());
                int left_id = (node["left_id"].as<int>());
                int right_id = (node["right_id"].as<int>());
                get_condition_node(node_id)->connect(get_condition_node(left_id), get_condition_node(right_id));
                spdlog::info("condition node_{} connect to node_{} & node_{}", node_id, left_id, right_id);
            }
        }
        //-----------------------------------------------------------------action_node----------------------------------------------------
        for (const auto &node : config["decision_tree_1"])
        {
            if (node["node_type"].as<std::string>() == "action")
            {
                int id = node["id"].as<int>();
                auto action_node = std::make_shared<sp_decision::ActionNode>(id);
                std::string action_name = node["action"].as<std::string>();
                std::string param_list = node["param"].as<std::string>();
                std::stringstream ss(param_list);
                std::string item;
                std::vector<double> param;
                // 使用getline和,分割字符串
                while (std::getline(ss, item, ','))
                {
                    param.push_back(std::stod(item));
                }
                action_node->set_action(id, action_name, param);
                action_nodes_.push_back(action_node);
            }
        }
        //---------------------------------------------------------------observer_node-------------------------------------------------
        for (const auto &observer_node : config["decision_tree_1"])
        {
            if (observer_node["node_type"].as<std::string>() == "sequence")
            {
                auto sequence_node = std::make_shared<Sequence>(observer_node["id"].as<int>());
                observer_nodes_.push_back(sequence_node);
                if (observer_node["action_list"])
                {
                    spdlog::info("sequence node_{} created with action list:", observer_node["id"].as<int>());
                    for (const auto &action : observer_node["action_list"])
                    {
                        spdlog::info("action node_{}", action.as<int>());
                        sequence_node->add_action_node(get_action_node(action.as<int>()));
                    }
                }
                for (const auto &node : config["decision_tree_1"])
                {
                    if (node["node_type"].as<std::string>() == "condition")
                    {
                        int condition_id = (node["id"].as<int>());
                        if (node["left_observer_id"].as<int>() == observer_node["id"].as<int>())
                            get_condition_node(condition_id)->connect_observer(sequence_node.get(), nullptr);
                        else if (node["right_observer_id"].as<int>() == observer_node["id"].as<int>())
                            get_condition_node(condition_id)->connect_observer(nullptr, sequence_node.get());
                    }
                }
            }
        }
    }

    void BehaviorTree::behavior_tree_run_()
    {

        rclcpp::executors::MultiThreadedExecutor executor;
        // 添加节点到执行器
        for (auto node : action_nodes_)
            executor.add_node(node);
        executor.add_node(head_node_);

        head_node_->start_judge();
        // 让执行器同时 spin 这些节点
        executor.spin();
    }

    ConditionNode *BehaviorTree::get_condition_node(int id)
    {
        if (id == 0)
            return nullptr;
        for (auto &condition_node : condition_nodes_)
        {
            if (condition_node->node_id_ == id)
                return condition_node.get();
        }
        return nullptr;
    }

    std::shared_ptr<ActionNode> BehaviorTree::get_action_node(int id)
    {
        if (id == 0)
            return nullptr;
        for (auto &action_node : action_nodes_)
        {
            if (action_node->action_id_ == id)
                return action_node;
        }
        return nullptr;
    }

}
