//
// Created by Jrinn on 2021/8/22.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainWindow.h" resolved

#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QMessageBox>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setWindowTitle("仲裁侦测助手  作者：Jrinn");
    setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    connect(ui->pushButton_exit, &QPushButton::clicked, &QApplication::quit);
    connect(ui->pushButton_refresh, &QPushButton::clicked, this, &MainWindow::refresh);
    request = new QNetworkRequest(QUrl("https://api.warframestat.us/pc/zh/arbitration"));
    accessManager = new QNetworkAccessManager;
    connect(accessManager, &QNetworkAccessManager::finished, this, &MainWindow::refreshText);
    box = new QMessageBox(this);
    box->setDefaultButton(QMessageBox::Ok);
    box->setWindowFlags(box->windowFlags() | Qt::WindowStaysOnTopHint);
    box->setWindowIcon(QIcon(":/icon.ico"));
    box->setWindowTitle("提示");
    connect(this, &MainWindow::showBox, box, &QMessageBox::show);
    trayIcon = new TrayIcon(this);
    trayIcon->show();
    timer = new QTimer;
    connect(timer, &QTimer::timeout, this, &MainWindow::on_timeout);
    timer->start(60 * 1000);
    refresh();
}

MainWindow::~MainWindow() {
    delete accessManager;
    delete request;
    delete reg;
    delete trayIcon;
    delete timer;
    delete ui;
}

void MainWindow::refresh() {
    ui->pushButton_refresh->setEnabled(false);
    ui->pushButton_refresh->setText("刷新中");
    accessManager->get(*request);
}

void MainWindow::refreshText(QNetworkReply *reply) {
    QJsonDocument document = QJsonDocument::fromJson(reply->readAll());
    QString str;
    if (!document.isNull() && document.isObject()) {
        QJsonObject obj = document.object();
        if (obj.contains("node")) {
            QRegularExpressionMatch match = reg->match(obj.value("node").toString());
            str = match.captured(1);
            ui->label_node->setText("节点：" + match.captured(1));
            ui->label_planet->setText("星球：" + match.captured(2));
        }
        if (obj.contains("type")) {
            ui->label_mode->setText("模式：" + obj.value("type").toString());
        }
        if (obj.contains("enemy")) {
            ui->label_enemy->setText("派系：" + obj.value("enemy").toString());
        }
    }
    ui->pushButton_refresh->setText("手动刷新");
    ui->pushButton_refresh->setEnabled(true);
    if (node_list.contains(str.trimmed())) {
        box->setText("现在是Infested防御啦！\n" + ui->label_node->text() + "\n" + ui->label_planet->text());
        emit showBox();
    }
}

QList<QString> MainWindow::node_list = {"Lares", "Kala-azar", "Romula", "Coba", "Sinai", "Kadesh", "Larzac", "Ur",
                                        "Akkad", "Seimeni",
                                        "Sechura", "Hyf", "Sangeru"};

void MainWindow::on_timeout() {
    if (QTime::currentTime().minute() == 6)
        refresh();
}
