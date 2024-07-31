#ifndef ACTION_NODE
#define ACTION_NODE
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <robot_action/action/common_action.hpp>
#include <iostream>
#include <random>

#include "tools/logger.hpp"
namespace sp_decision
{
    using CommonAction = robot_action::action::CommonAction;
    using GoalHandleCommonAction = rclcpp_action::ClientGoalHandle<CommonAction>;
    enum ActionState
    {
        INACTIVE,
        RUNNING,
        SUCCESS,
        FAIL
    };
    // 观察者类接口
    class Observer
    {
    public:
        virtual void update(ActionState state) = 0;
        virtual void tick_activate() = 0;
        virtual void tick_deactivate() = 0;
    };
    class ActionNode : public rclcpp::Node, public Observer
    {
    public:
        ActionNode(int id);
        ~ActionNode();

        void tick_activate() override;           // 激活
        void tick_deactivate() override;         // 关闭
        void update(ActionState state) override; // 被观察者调用

        void set_action(int id, std::string name, std::vector<double> param);
        void send_goal();
        void cancel_goal();
        void goal_response_callback(typename GoalHandleCommonAction::SharedPtr goal_handle);
        void feedback_callback(
            GoalHandleCommonAction::SharedPtr goal_handle,
            const std::shared_ptr<const CommonAction::Feedback> feedback);
        void result_callback(const GoalHandleCommonAction::WrappedResult &result);
        void set_observers(std::vector<std::reference_wrapper<Observer>> observers);
        void notify_observers(ActionState state);

        int action_id_;

    private:
        std::string action_name_;
        std::vector<double> action_param_;
        rclcpp_action::Client<CommonAction>::SharedPtr client_ptr_;
        std::vector<std::reference_wrapper<Observer>> observers_;
        ActionState action_state_;
    };

}
#endif