#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <robot_action/action/common_action.hpp>
#include "tools/logger.hpp"

using CommonAction = robot_action::action::CommonAction;
using GoalHandleCommonAction = rclcpp_action::ServerGoalHandle<CommonAction>;

class SimActionServer : public rclcpp::Node
{
public:
    SimActionServer()
        : Node("fibonacci_action_server")
    {
        this->action_server_ = rclcpp_action::create_server<CommonAction>(
            this,
            "common_action",
            std::bind(&SimActionServer::handle_goal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&SimActionServer::handle_cancel, this, std::placeholders::_1),
            std::bind(&SimActionServer::handle_accepted, this, std::placeholders::_1));
    }

private:
    rclcpp_action::Server<CommonAction>::SharedPtr action_server_;

    rclcpp_action::GoalResponse handle_goal(const rclcpp_action::GoalUUID &uuid, std::shared_ptr<const CommonAction::Goal> goal)
    {
        spdlog::info("Received goal request from node_{}", goal->action_id);
        spdlog::info("action_name : {}", goal->action_name);
        spdlog::info("Parameters:");
        for (auto i : goal->parameters)
        {
            spdlog::info("{}", i);
        }
        (void)uuid;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(const std::shared_ptr<GoalHandleCommonAction> goal_handle)
    {
        spdlog::info("Received cancel request");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandleCommonAction> goal_handle)
    {
        using namespace std::placeholders;
        std::thread{std::bind(&SimActionServer::execute, this, _1), goal_handle}.detach();
    }

    void execute(const std::shared_ptr<GoalHandleCommonAction> goal_handle)
    {
        spdlog::info("Executing goal");
        rclcpp::Rate loop_rate(1);
        const auto goal = goal_handle->get_goal();
        auto feedback = std::make_shared<CommonAction::Feedback>();
        auto &sequence = feedback->states;

        auto result = std::make_shared<CommonAction::Result>();

        for (int i = 0; i < 10 && rclcpp::ok(); ++i)
        {
            if (goal_handle->is_canceling())
            {
                goal_handle->canceled(result);
                spdlog::info("Goal canceled");
                return;
            }
            sequence.push_back(i);
            goal_handle->publish_feedback(feedback);
            spdlog::info("Publish feedback:{}",i);

            loop_rate.sleep();
        }

        if (rclcpp::ok())
        {
            result->result = sequence.back();
            goal_handle->succeed(result);
            spdlog::info("Goal succeeded");
        }
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SimActionServer>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
