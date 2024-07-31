#include "perception/blackboard.hpp"

namespace sp_decision
{
    BlackBoard::BlackBoard()
        : Node("blackboard")
    {
        RCLCPP_INFO(get_logger(), "BlackBoard has been created.");
    }
    BlackBoard::~BlackBoard()
    {
        RCLCPP_INFO(get_logger(), "BlackBoard has been destroyed.");
    }
    bool BlackBoard::check_key(std::string key)
    {
        auto it = map_test_.find(key);
        if (it != map_test_.end())
            return true;
        else
            return false;
    }
    double BlackBoard::get_value(std::string key)
    {
        std::lock_guard<std::mutex> lock(map_mutex_);
        if(check_key(key))
        {
            spdlog::info("Variable {} is found, value is {}", key, *map_test_[key]);
            return *map_test_[key];
        }
        else
        {
            spdlog::info("Variable {} is not found.", key);
            return 0.000001;
        }
    }
    void BlackBoard::set_value(std::string key, double value)
    {
        std::unique_lock<std::mutex> lock(map_mutex_);
        auto it = map_test_.find(key);
        if (it != map_test_.end())
        {
            *it->second = value;
            spdlog::info("Variable {} is updated, new value is {}", key, *it->second);
        }
        else
        {
            map_test_[key] = std::make_shared<double>(value);
        }
        lock.unlock(); // 显式解锁
    }
}