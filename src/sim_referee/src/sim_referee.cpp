#include "sim_referee.h"
#include "ui_sim_referee.h"

SimReferee::SimReferee(QWidget *parent)
    : QWidget(parent), ui(new Ui::SimReferee)
{
    ui->setupUi(this);
    node_ = std::make_shared<rclcpp::Node>("sim_referee");
    referee_info_pub_ = node_->create_publisher<robot_msg::msg::RefereeInfoMsg>("/referee_info", 10);
    enemy_hp_pub_ = node_->create_publisher<robot_msg::msg::RobotHpMsg>("/Enemy_robot_HP", 10);
    team_hp_pub_ = node_->create_publisher<robot_msg::msg::RobotHpMsg>("/Team_robot_HP", 10);
    referee_info_init();
    enemy_hp_init();
    team_hp_init();
    ros_timer = new QTimer(this);
    connect(ros_timer, SIGNAL(timeout()), this, SLOT(spinOnce()));
    ros_timer->start(100); // set the rate to 100ms  You can change this if you want to increase/decrease update rate
    last_time = node_->get_clock()->now();
    match_timer = new QTimer(this);
    connect(match_timer, SIGNAL(timeout()), this, SLOT(countdown()));
    match_timer->start(50);
    // last_target_x_ = 0;
    // last_target_y_ = 0;
    // current_target_x_ = 0;
    // current_target_y_ = 0;
    // configWindow = new Map_select();
    // configWindow->loadImage("/home/lp1/sp_decision_ui/src/sp_decision_ui/map.png");
}

SimReferee::~SimReferee()
{
    delete ui;
}
void SimReferee::spinOnce()
{
    referee_info_pub_->publish(referee_info);
    enemy_hp_pub_->publish(enemy_hp);
    team_hp_pub_->publish(team_hp);
    std::stringstream ss;
    ss << "stage:" << static_cast<double>(referee_info.game_progress);
    QString qstr = QString::fromStdString(ss.str());
    ui->label_stage->setText(qstr); // 显示比赛阶段
    std::stringstream ss_3;
    ss_3 << static_cast<int>(enemy_hp.hero_hp);
    QString qstr_3 = QString::fromStdString(ss_3.str());
    ui->label_enemy_hero_hp->setText(qstr_3); // 敌方血量1
    std::stringstream ss_4;
    ss_4 << static_cast<int>(enemy_hp.engineer_hp);
    QString qstr_4 = QString::fromStdString(ss_4.str());
    ui->label_enemy_engineer_hp->setText(qstr_4); // 敌方血量2
    std::stringstream ss_5;
    ss_5 << static_cast<int>(enemy_hp.infantry_3_hp);
    QString qstr_5 = QString::fromStdString(ss_5.str());
    ui->label_enemy_infantry_3_hp->setText(qstr_5); // 敌方血量3
    std::stringstream ss_6;
    ss_6 << static_cast<int>(enemy_hp.infantry_4_hp);
    QString qstr_6 = QString::fromStdString(ss_6.str());
    ui->label_enemy_infantry_4_hp->setText(qstr_6); // 敌方血量4
    std::stringstream ss_7;
    ss_7 << static_cast<int>(enemy_hp.infantry_5_hp);
    QString qstr_7 = QString::fromStdString(ss_7.str());
    ui->label_enemy_infantry_5_hp->setText(qstr_7); // 敌方血量5
    std::stringstream ss_8;
    ss_8 << static_cast<int>(enemy_hp.sentry_hp);
    QString qstr_8 = QString::fromStdString(ss_8.str());
    ui->label_enemy_sentry_hp->setText(qstr_8); // 敌方血量6
    std::stringstream ss_9;
    ss_9 << static_cast<int>(enemy_hp.outpost_hp);
    QString qstr_9 = QString::fromStdString(ss_9.str());
    ui->label_enemy_outpost_hp->setText(qstr_9); // 敌方血量7
    std::stringstream ss_10;
    ss_10 << static_cast<int>(enemy_hp.base_hp);
    QString qstr_10 = QString::fromStdString(ss_10.str());
    ui->label_enemy_base_hp->setText(qstr_10); // 敌方血量8

    std::stringstream ss_31;
    ss_31 << static_cast<int>(team_hp.hero_hp);
    QString qstr_31 = QString::fromStdString(ss_31.str());
    ui->label_team_hero_hp->setText(qstr_31); // 我方血量1
    std::stringstream ss_41;
    ss_41 << static_cast<int>(team_hp.engineer_hp);
    QString qstr_41 = QString::fromStdString(ss_41.str());
    ui->label_team_engineer_hp->setText(qstr_41); // 我方血量2
    std::stringstream ss_51;
    ss_51 << static_cast<int>(team_hp.infantry_3_hp);
    QString qstr_51 = QString::fromStdString(ss_51.str());
    ui->label_team_infantry_3_hp->setText(qstr_51); // 我方血量3
    std::stringstream ss_61;
    ss_61 << static_cast<int>(team_hp.infantry_4_hp);
    QString qstr_61 = QString::fromStdString(ss_61.str());
    ui->label_team_infantry_4_hp->setText(qstr_61); // 我方血量4
    std::stringstream ss_71;
    ss_71 << static_cast<int>(team_hp.infantry_5_hp);
    QString qstr_71 = QString::fromStdString(ss_71.str());
    ui->label_team_infantry_5_hp->setText(qstr_71); // 我方血量5
    std::stringstream ss_81;
    ss_81 << static_cast<int>(team_hp.sentry_hp);
    QString qstr_81 = QString::fromStdString(ss_81.str());
    ui->label_team_sentry_hp->setText(qstr_81); // 我方血量6
    std::stringstream ss_91;
    ss_91 << static_cast<int>(team_hp.outpost_hp);
    QString qstr_91 = QString::fromStdString(ss_91.str());
    ui->label_team_outpost_hp->setText(qstr_91); // 我方血量7
    std::stringstream ss_101;
    ss_101 << static_cast<int>(team_hp.base_hp);
    QString qstr_101 = QString::fromStdString(ss_101.str());
    ui->label_team_base_hp->setText(qstr_101); // 我方血量8
                                               // target_pos_update();
}
void SimReferee::countdown()
{
    if (referee_info.stage_remain_time == 0) // 倒计时为0自动进入下一阶段
    {
        switch (static_cast<int>(referee_info.game_progress))
        {
        case 1:
            on_button_stage2_clicked();
            break;
        case 2:
            on_button_stage3_clicked();
            break;
        case 3:
            on_button_stage4_clicked();
            break;
        case 4:
            on_button_stage5_clicked();
            break;
        default:
            break;
        }
    }
    if ((node_->get_clock()->now() - last_time).seconds() >= 1 && referee_info.stage_remain_time > 0)
    {
        referee_info.stage_remain_time--;

        last_time = node_->get_clock()->now();
    }
    ui->slider_time->setValue(referee_info.stage_remain_time);
    std::stringstream ss;
    ss << "remainder" << referee_info.stage_remain_time;
    QString qstr = QString::fromStdString(ss.str());
    ui->label_time->setText(qstr);
}
void SimReferee::referee_info_init()
{
    referee_info.game_progress = 1;
    referee_info.stage_remain_time = 180;
    referee_info.target_x = 0.0;
    referee_info.target_y = 0.0;
    referee_info.key = 0;
}
void SimReferee::enemy_hp_init()
{
    enemy_hp.hero_hp = 500;
    enemy_hp.engineer_hp = 250;
    enemy_hp.infantry_3_hp = 400;
    enemy_hp.infantry_4_hp = 400;
    enemy_hp.infantry_5_hp = 400;
    enemy_hp.sentry_hp = 400;
    enemy_hp.outpost_hp = 1500;
    enemy_hp.base_hp = 5000;
    update_enemy_hp();
}
void SimReferee::team_hp_init()
{
    team_hp.hero_hp = 500;
    team_hp.engineer_hp = 250;
    team_hp.infantry_3_hp = 400;
    team_hp.infantry_4_hp = 400;
    team_hp.infantry_5_hp = 400;
    team_hp.sentry_hp = 400;
    team_hp.outpost_hp = 1500;
    team_hp.base_hp = 5000;
    update_team_hp();
}
void SimReferee::update_enemy_hp()
{
    ui->slider_enemy_hero->setValue(enemy_hp.hero_hp);
    ui->slider_enemy_engineer->setValue(enemy_hp.engineer_hp);
    ui->slider_enemy_infantry_3->setValue(enemy_hp.infantry_3_hp);
    ui->slider_enemy_infantry_4->setValue(enemy_hp.infantry_4_hp);
    ui->slider_enemy_infantry_5->setValue(enemy_hp.infantry_5_hp);
    ui->slider_enemy_sentry->setValue(enemy_hp.sentry_hp);
    ui->slider_enemy_outpost->setValue(enemy_hp.outpost_hp);
    ui->slider_enemy_base->setValue(enemy_hp.base_hp);
}
void SimReferee::update_team_hp()
{
    ui->slider_team_hero->setValue(team_hp.hero_hp);
    ui->slider_team_engineer->setValue(team_hp.engineer_hp);
    ui->slider_team_infantry_3->setValue(team_hp.infantry_3_hp);
    ui->slider_team_infantry_4->setValue(team_hp.infantry_4_hp);
    ui->slider_team_infantry_5->setValue(team_hp.infantry_5_hp);
    ui->slider_team_sentry->setValue(team_hp.sentry_hp);
    ui->slider_team_outpost->setValue(team_hp.outpost_hp);
    ui->slider_team_base->setValue(team_hp.base_hp);
}
void SimReferee::target_pos_update(){
    // current_target_x_=configWindow->target_x;
    // current_target_y_=configWindow->target_y;
    if(last_target_x_!=current_target_x_&&last_target_y_!=current_target_y_)
    {
        ui->target_x->setValue(current_target_x_);
        ui->target_y->setValue(current_target_y_);
        last_target_x_=current_target_x_;
        last_target_y_=current_target_y_;
    }
}
void SimReferee::on_slider_time_sliderMoved(int position)
{
    referee_info.stage_remain_time = position;
}
void SimReferee::on_button_stage1_clicked()
{
    referee_info.game_progress = 1;
    referee_info.stage_remain_time = 180;
}
void SimReferee::on_button_stage2_clicked()
{
    referee_info.game_progress = 2;
    referee_info.stage_remain_time = 15;
}

void SimReferee::on_button_stage3_clicked()
{
    referee_info.game_progress = 3;
    referee_info.stage_remain_time = 5;
}

void SimReferee::on_button_stage4_clicked()
{
    referee_info.game_progress = 4;
    referee_info.stage_remain_time = 420;
}

void SimReferee::on_button_stage5_clicked()
{
    referee_info.game_progress = 5;
    referee_info.stage_remain_time = 10;
}

void SimReferee::on_slider_enemy_hero_sliderMoved(int position)
{
    enemy_hp.hero_hp = position;
}

void SimReferee::on_slider_enemy_engineer_sliderMoved(int position)
{
    enemy_hp.engineer_hp = position;
}

void SimReferee::on_slider_enemy_infantry_3_sliderMoved(int position)
{
    enemy_hp.infantry_3_hp = position;
}

void SimReferee::on_slider_enemy_infantry_4_sliderMoved(int position)
{
    enemy_hp.infantry_4_hp = position;
}

void SimReferee::on_slider_enemy_infantry_5_sliderMoved(int position)
{
    enemy_hp.infantry_5_hp = position;
}

void SimReferee::on_slider_enemy_sentry_sliderMoved(int position)
{
    enemy_hp.sentry_hp = position;
}

void SimReferee::on_slider_enemy_outpost_sliderMoved(int position)
{
    enemy_hp.outpost_hp = position;
}

void SimReferee::on_slider_enemy_base_sliderMoved(int position)
{
    enemy_hp.base_hp = position;
}

void SimReferee::on_target_x_valueChanged(double arg1)
{
    target_x_ = arg1;
}
void SimReferee::on_target_y_valueChanged(double arg1)
{
    target_y_ = arg1;
}

void SimReferee::on_slider_team_hero_sliderMoved(int position)
{
    team_hp.hero_hp = position;
}

void SimReferee::on_slider_team_engineer_sliderMoved(int position)
{
    team_hp.engineer_hp = position;
}

void SimReferee::on_slider_team_infantry_3_sliderMoved(int position)
{
    team_hp.infantry_3_hp = position;
}

void SimReferee::on_slider_team_infantry_4_sliderMoved(int position)
{
    team_hp.infantry_4_hp = position;
}

void SimReferee::on_slider_team_infantry_5_sliderMoved(int position)
{
    team_hp.infantry_5_hp = position;
}

void SimReferee::on_slider_team_sentry_sliderMoved(int position)
{
    team_hp.sentry_hp = position;
}

void SimReferee::on_slider_team_outpost_sliderMoved(int position)
{
    team_hp.outpost_hp = position;
}

void SimReferee::on_slider_team_base_sliderMoved(int position)
{
    team_hp.base_hp = position;
}

void SimReferee::on_botto_target_clicked()
{
    referee_info.target_x = target_x_;
    referee_info.target_y = target_y_;
    referee_info.key = key_;
    referee_info_pub_->publish(referee_info);
    referee_info.target_x = 0.0;
    referee_info.target_y = 0.0;
    referee_info.key = 0;
}

// void SimReferee::on_botton_key_clicked()
// {
//     referee_info.target_x = target_x_;
//     referee_info.target_y = target_y_;
//     referee_info.key = key_;
//     referee_info_pub_->publish(referee_info);
//     referee_info.target_x = 0.0;
//     referee_info.target_y = 0.0;
//     referee_info.key = 0;
// }

// void SimReferee::on_key_edit_textChanged()
// {
//     QString value = ui->key_edit->toPlainText();
//     QByteArray byteArray = value.toLatin1();
//     const char *charArray = byteArray.constData();
//     key_ = *charArray;
// }
void SimReferee::on_pushButton_3_clicked()
{
    // configWindow->show();
}
