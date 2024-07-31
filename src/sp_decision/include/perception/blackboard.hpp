#ifndef BLACKBOARD
#define BLACKBOARD
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>
#include <random>
#include "tools/logger.hpp"
namespace sp_decision
{
    class BlackBoard : public rclcpp::Node
    {
    public:
        BlackBoard();
        ~BlackBoard();
        bool check_key(std::string key);
        double get_value(std::string key);
        void set_value(std::string key, double value);
    private:
        std::map<std::string, std::shared_ptr<double>> map_test_;
        std::mutex map_mutex_;
    };

}
#endif