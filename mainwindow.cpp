#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "settings.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileTableModel(new QStandardItemModel)
    , fileListModel(new QFileSystemModel)
    , history(new HistoryWindow)
{
    ui->setupUi(this);
    activateHistory();

    QObject::connect(ui->settings, SIGNAL(clicked()), this, SLOT(activateSettings()));
    QObject::connect(ui->history, SIGNAL(clicked()), this, SLOT(activateHistory()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete fileListModel;
    delete fileTableModel;
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

void MainWindow::clearFrame(){
    for(auto& x : ui->generalFrame->children()){
        delete x;
    }
}
