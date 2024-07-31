#include <iostream>
#include <vector>
#include <functional>

#include "tools/logger.hpp"
#include "node/action_node.hpp"
namespace sp_decision
{
    
    class Sequence : public Observer
    {
    public:
        Sequence(int id);
        ~Sequence();
        void tick_activate() override;           // 激活
        void tick_deactivate() override;         // 关闭
        void update(ActionState state) override; // 被观察者调用
        void add_action_node(std::shared_ptr<ActionNode> node);  // 添加节点
        void switch_next_action();               // 切换到下一个节点执行
        void cancel_current_action();            // 取消当前节点执行
        void notify_observers();
        void change_state(ActionState state);

    private:
        int sequence_id_;
        std::vector<std::shared_ptr<ActionNode>> action_nodes_;
        int symbol_; // 指示当前运行节点
        std::vector<std::reference_wrapper<Observer>> observers_;
        ActionState sequence_state_;
    };
}
