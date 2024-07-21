#include <QApplication>
#include <rclcpp/rclcpp.hpp>
#include "sim_referee.h"

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
        QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication a(argc, argv);
    SimReferee w;

    w.show();
    return a.exec();
}