//
// Created by Jrinn on 2021/8/23.
//

#ifndef WARFRAME_N_TRAYICON_H
#define WARFRAME_N_TRAYICON_H

#include <QSystemTrayIcon>
#include <QMenu>
class TrayIcon : public QSystemTrayIcon {
public:
    explicit TrayIcon(QWidget *parent = nullptr);
    ~TrayIcon() override;
    QWidget * mainWindow;
private:
    QMenu *menu;
    QAction* action_show,*action_exit;
private slots:
    void on_activated(QSystemTrayIcon::ActivationReason reason);
};


#endif //WARFRAME_N_TRAYICON_H
