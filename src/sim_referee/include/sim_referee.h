#ifndef SIM_REFEREE_H
#define SIM_REFEREE_H

#include <QWidget>
#include <qtimer.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include "robot_msg/msg/referee_info_msg.hpp"
#include "robot_msg/msg/robot_hp_msg.hpp"
namespace Ui
{
    class SimReferee;
}

class SimReferee : public QWidget
{
    Q_OBJECT

public:
    explicit SimReferee(QWidget *parent = nullptr);
    ~SimReferee();
    robot_msg::msg::RefereeInfoMsg referee_info;
    robot_msg::msg::RobotHpMsg enemy_hp;
    robot_msg::msg::RobotHpMsg team_hp;
public slots:
    void spinOnce();  // 更新label信息
    void countdown(); // 倒计时
private slots:
    void on_slider_time_sliderMoved(int position);
    void on_button_stage1_clicked();
    void on_button_stage2_clicked();
    void on_button_stage3_clicked();
    void on_button_stage4_clicked();
    void on_button_stage5_clicked();
    void on_slider_enemy_hero_sliderMoved(int position);
    void on_slider_enemy_engineer_sliderMoved(int position);
    void on_slider_enemy_infantry_3_sliderMoved(int position);
    void on_slider_enemy_infantry_4_sliderMoved(int position);
    void on_slider_enemy_infantry_5_sliderMoved(int position);
    void on_slider_enemy_sentry_sliderMoved(int position);
    void on_slider_enemy_outpost_sliderMoved(int position);
    void on_slider_enemy_base_sliderMoved(int position);
    void on_target_x_valueChanged(double arg1);
    void on_slider_team_hero_sliderMoved(int position);
    void on_slider_team_engineer_sliderMoved(int position);
    void on_slider_team_infantry_3_sliderMoved(int position);
    void on_slider_team_infantry_4_sliderMoved(int position);
    void on_slider_team_infantry_5_sliderMoved(int position);
    void on_slider_team_sentry_sliderMoved(int position);
    void on_slider_team_outpost_sliderMoved(int position);
    void on_slider_team_base_sliderMoved(int position);
    void on_botto_target_clicked();
    void on_target_y_valueChanged(double arg1);
    void on_pushButton_3_clicked();

private:
    Ui::SimReferee *ui;
    QTimer *ros_timer;
    QTimer *match_timer; // 用于比赛计时
    rclcpp::Time last_time;
    double target_x_;
    double target_y_;
    char key_;
    void referee_info_init(); // 初始化裁判系统消息
    void enemy_hp_init();     // 初始化敌方血量
    void team_hp_init();      // 初始化敌方血量
    void update_enemy_hp();      // 更新敌方血量滑条
    void update_team_hp();       // 更新敌方血量滑条
    void target_pos_update();    // 更新目标点坐标
    double last_target_x_;
    double last_target_y_;
    double current_target_x_;
    double current_target_y_;
    //20240721 todo:地图选点
    // Map_select *configWindow;
    std::shared_ptr<rclcpp::Node> node_;
    rclcpp::Publisher<robot_msg::msg::RefereeInfoMsg>::SharedPtr referee_info_pub_;
    rclcpp::Publisher<robot_msg::msg::RobotHpMsg>::SharedPtr enemy_hp_pub_;
    rclcpp::Publisher<robot_msg::msg::RobotHpMsg>::SharedPtr team_hp_pub_;
};

#endif // SIM_REFEREE_H
