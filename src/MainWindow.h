//
// Created by Jrinn on 2021/8/22.
//

#ifndef WARFRAME_N_MAINWINDOW_H
#define WARFRAME_N_MAINWINDOW_H

#include <QWidget>
#include <QtNetwork/QtNetwork>
#include <QRegularExpression>
#include <QMessageBox>
#include <QTimer>
#include "TrayIcon.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget {
Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *accessManager;
    QNetworkRequest *request;
    QRegularExpression *reg = new QRegularExpression("(.*)\\((.*)\\)");
    static QList<QString> node_list;
    QMessageBox *box;
    QTimer *timer;
    TrayIcon *trayIcon;
private slots:

    void refresh();

    void on_timeout();

    void refreshText(QNetworkReply *reply);

signals:

    void showBox();

};


#endif //WARFRAME_N_MAINWINDOW_H
