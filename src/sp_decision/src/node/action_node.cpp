#include "node/action_node.hpp"

namespace sp_decision
{
    ActionNode::ActionNode(int id) : Node("action_node_" + std::to_string(id))
    {
        this->client_ptr_ = rclcpp_action::create_client<CommonAction>(this, "common_action");
        this->action_state_ = ActionState::INACTIVE;
    }

    ActionNode::~ActionNode()
    {
        spdlog::info("ActionNode:{} destroyed", this->get_name());
    }

    void ActionNode::tick_activate()
    {
        send_goal();
    }
    void ActionNode::tick_deactivate()
    {
        cancel_goal();
    }
    void ActionNode::update(ActionState state)
    {
        spdlog::info("todo");
    }
    void ActionNode::set_action(int id, std::string name, std::vector<double> param)
    {
        this->action_id_ = id;
        this->action_name_ = name;
        this->action_param_ = param;
    }

    void ActionNode::send_goal()
    {
        if (!this->client_ptr_->wait_for_action_server(std::chrono::seconds(10)))
        {
            spdlog::info("Action server not available after waiting");
            this->action_state_ = ActionState::FAIL;
            notify_observers(action_state_);
            rclcpp::shutdown();
            return;
        }

        auto goal_msg = CommonAction::Goal();
        goal_msg.action_id = action_id_;
        goal_msg.action_name = action_name_;
        for (auto i : action_param_)
        {
            goal_msg.parameters.push_back(i);
        }
        spdlog::info("Sending goal request from node_{}", goal_msg.action_id);
        this->action_state_ = ActionState::RUNNING;
        notify_observers(action_state_);
        auto send_goal_options = rclcpp_action::Client<CommonAction>::SendGoalOptions();
        send_goal_options.goal_response_callback = std::bind(&ActionNode::goal_response_callback, this, std::placeholders::_1);
        send_goal_options.feedback_callback = std::bind(&ActionNode::feedback_callback, this, std::placeholders::_1, std::placeholders::_2);
        send_goal_options.result_callback = std::bind(&ActionNode::result_callback, this, std::placeholders::_1);

        this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
    }

    void ActionNode::cancel_goal()
    {
        this->client_ptr_->async_cancel_all_goals();
        this->action_state_ = ActionState::FAIL;
        notify_observers(action_state_);
        spdlog::info("action_{} canceled", action_id_);
    }
    void ActionNode::goal_response_callback(typename GoalHandleCommonAction::SharedPtr goal_handle)
    {
        if (!goal_handle)
        {
            this->action_state_ = ActionState::FAIL;
            notify_observers(action_state_);
            spdlog::info("Goal was rejected by server");
        }
        else
        {
            this->action_state_ = ActionState::RUNNING;
            notify_observers(action_state_);
            spdlog::info("Goal accepted by server, waiting for result");
        }
    }
    void ActionNode::feedback_callback(GoalHandleCommonAction::SharedPtr goal_handle, const std::shared_ptr<const CommonAction::Feedback> feedback)
    {
        spdlog::info("Next number in sequence received: {}", feedback->states.back());
    }

    void ActionNode::result_callback(const GoalHandleCommonAction::WrappedResult &result)
    {
        switch (result.code)
        {
        case rclcpp_action::ResultCode::SUCCEEDED:
            this->action_state_ = ActionState::SUCCESS;
            notify_observers(action_state_);
            spdlog::info("Result received");
            break;
        case rclcpp_action::ResultCode::ABORTED:
            this->action_state_ = ActionState::FAIL;
            notify_observers(action_state_);
            spdlog::info("Goal was aborted");
            return;
        case rclcpp_action::ResultCode::CANCELED:
            this->action_state_ = ActionState::FAIL;
            notify_observers(action_state_);
            spdlog::info("Goal was canceled");
            return;
        default:
            this->action_state_ = ActionState::FAIL;
            notify_observers(action_state_);
            spdlog::info("Unknown result code");
            return;
        }
        spdlog::info("Result: {}", result.result->result);
    }
    void ActionNode::set_observers(std::vector<std::reference_wrapper<Observer>> observers)
    {
        for (auto observer : observers)
        {
            observers_.push_back(observer);
        }
    }
    void ActionNode::notify_observers(ActionState state)
    {
        for (Observer &observer : observers_)
        {
            observer.update(action_state_);
        }
    }

}
