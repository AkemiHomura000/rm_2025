#include<iostream>
#include <QApplication>
#include <spdlog/spdlog.h>

#include "mainwindow.h"

int main(int argc, char* argv[])
{
    spdlog::set_level(spdlog::level::debug);
    QApplication a(argc, argv);
    MainWindow w;
    w.setGeometry(100, 100, 1200, 600);
    w.show();
    return a.exec();
}
