#include "node/observe_node.hpp"

namespace sp_decision
{
    Sequence::Sequence(int id)
    {
        sequence_id_ = id;
        sequence_state_ = ActionState::INACTIVE;
        symbol_ = -1;
    }
    Sequence::~Sequence()
    {
        spdlog::info("Sequence node_{} has been destroyed.", sequence_id_);
    }
    void Sequence::tick_activate()
    {
        switch (sequence_state_)
        {
        case ActionState::INACTIVE:
            change_state(ActionState::RUNNING);
            switch_next_action();
            break;
        case ActionState::RUNNING:
            break;
        case ActionState::SUCCESS:
            break;
        case ActionState::FAIL:
            break;
        }
    }
    void Sequence::tick_deactivate()
    {
        switch (sequence_state_)
        {
        case ActionState::INACTIVE:
            break;
        case ActionState::RUNNING:
            change_state(ActionState::INACTIVE);
            cancel_current_action();
            break;
        case ActionState::SUCCESS:
            change_state(ActionState::INACTIVE);
            break;
        case ActionState::FAIL:
            change_state(ActionState::INACTIVE);
            break;
        }
    }
    void Sequence::update(ActionState state)
    {
        if (symbol_ != -1 && state == ActionState::FAIL)
            change_state(ActionState::FAIL);
        else if (symbol_ == action_nodes_.size() && state == ActionState::SUCCESS)
            change_state(ActionState::SUCCESS);
        else if(state == ActionState::SUCCESS)
        {
            switch_next_action();
        }
    }
    void Sequence::add_action_node(std::shared_ptr<ActionNode> node)
    {
        action_nodes_.push_back(node);
        node->set_observers({std::ref(*this)});
    }
    void Sequence::switch_next_action()
    {
        symbol_++;
        spdlog::error("symbol : {} ", symbol_);
        if (symbol_ < action_nodes_.size())
        {
            action_nodes_[symbol_]->tick_activate();
        }
    }
    void Sequence::cancel_current_action()
    {
        if (symbol_ < action_nodes_.size())
        {
            action_nodes_[symbol_]->tick_deactivate();
        }
        symbol_ = -1;
    }
    void Sequence::notify_observers()
    {
        for (Observer &observer : observers_)
        {
            observer.update(sequence_state_);
        }
    }
    void Sequence::change_state(ActionState state)
    {
        sequence_state_ = state;
        // notify_observers();
    }
}
