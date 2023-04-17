
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,300);
    readFile();

    QObject::connect(ui->general, SIGNAL(clicked()), this, SLOT(handleButton()));
    QObject::connect(ui->settings, SIGNAL(clicked()), this, SLOT(test()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindow::onBagSizeChange(){

}

void MainWindow::MainWindow::newDataStream(){

}

void MainWindow::MainWindow::readFile(){
    model = new QStandardItemModel();

    QFile file("C:\\Users\\eskil\\Documents\\SRRP-GUI\\test.csv");
    if(file.open(QIODevice::ReadOnly)){
        int lineIndex = 0;
        QTextStream in(&file);

        while(!in.atEnd()){
            QString currentLine = in.readLine();
            QStringList lineToken = currentLine.split(";", Qt::SkipEmptyParts);

            int colIndex = 0;
            for(auto& token : lineToken){
                QStandardItem* item = new QStandardItem(token);
                model->setItem(lineIndex, colIndex, item);
                colIndex++;
            }
            lineIndex++;
        }
        file.close();
    }
    ui->tableView->setModel(model);
}

void MainWindow::MainWindow::handleButton(){
    ui->generalFrame->setVisible(!ui->generalFrame->isVisible());
}

void MainWindow::MainWindow::test(){
    readFile();
}

