#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settings.h"
#include "history.h"
#include "generalwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->generalFrame->setMinimumSize(QSize(950,0));
    activateGeneral();

    QObject::connect(ui->settings, SIGNAL(clicked()), this, SLOT(activateSettings()));
    QObject::connect(ui->history, SIGNAL(clicked()), this, SLOT(activateHistory()));
    QObject::connect(ui->general, SIGNAL(clicked()), this, SLOT(activateGeneral()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::activateSettings(){
    if(ui->generalFrame->layout()->objectName() == "settingsLayout") return;
    clearFrame();
    QHBoxLayout* settingsLayout = new QHBoxLayout(ui->generalFrame);  
    settingsLayout->addWidget(new SettingsWindow(ui->generalFrame));
    settingsLayout->setContentsMargins(0,0,0,0);
    ui->generalFrame->setLayout(settingsLayout);
    ui->generalFrame->layout()->setObjectName("settingsLayout");
}

void MainWindow::activateHistory(){
    if(ui->generalFrame->layout()->objectName() == "historyLayout") return;
    clearFrame();
    QHBoxLayout* historyLayout = new QHBoxLayout(ui->generalFrame);
    historyLayout->addWidget(new HistoryWindow(ui->generalFrame));
    historyLayout->setContentsMargins(0,0,0,0);
    ui->generalFrame->setLayout(historyLayout);
    ui->generalFrame->layout()->setObjectName("historyLayout");
}

void MainWindow::activateGeneral(){
    if(ui->generalFrame->layout()->objectName() == "generalLayout") return;
    clearFrame();
    QHBoxLayout* generalLayout = new QHBoxLayout(ui->generalFrame);
    generalLayout->addWidget(new GeneralWindow(ui->generalFrame));
    generalLayout->setContentsMargins(0,0,0,0);
    ui->generalFrame->setLayout(generalLayout);
    ui->generalFrame->layout()->setObjectName("generalLayout");
}

void MainWindow::test(){
    qDebug() << this->sender();
}

void MainWindow::clearFrame(){
    for(auto& x : ui->generalFrame->children()){
        delete x;
    }
}
