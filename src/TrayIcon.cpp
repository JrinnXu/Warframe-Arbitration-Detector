//
// Created by Jrinn on 2021/8/23.
//

#include "TrayIcon.h"
#include <QApplication>

TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(nullptr), mainWindow(parent) {
    setIcon(QIcon(":/icon.ico"));
    menu = new QMenu;
    action_show = new QAction("主界面");
    action_exit = new QAction("退出");
    connect(action_show, &QAction::triggered, mainWindow, &QWidget::show);
    connect(action_exit, &QAction::triggered, &QApplication::quit);
    menu->addAction(action_show);
    menu->addAction(action_exit);
    setContextMenu(menu);
    connect(this, &QSystemTrayIcon::activated, this, &TrayIcon::on_activated);
}

TrayIcon::~TrayIcon() {
    delete menu;
    delete action_exit;
    delete action_show;
}

void TrayIcon::on_activated(QSystemTrayIcon::ActivationReason reason) {
    if (reason == QSystemTrayIcon::DoubleClick)
        mainWindow->show();
}
