
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileTableModel(new QStandardItemModel)
    , fileListModel(new QFileSystemModel)
    , filecount{0}
{
    ui->setupUi(this);
    this->resize(1000,300);

    QString directory = "/home/eskild/Documents/SRRP-GUI/tests";
    ui->fileList->setModel(fileListModel);
    ui->fileList->setRootIndex(fileListModel->setRootPath(directory));

    QObject::connect(ui->fileList, SIGNAL(clicked(QModelIndex)), this, SLOT(readFile(QModelIndex)));
    QObject::connect(ui->general, SIGNAL(clicked()), this, SLOT(handleButton()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MainWindow::onBagSizeChange(){

}

void MainWindow::MainWindow::newDataStream(){

}

void MainWindow::MainWindow::readFile(QModelIndex index){
    QString itemText = index.data(Qt::DisplayRole).toString();
    QFile file(tr("/home/eskild/Documents/SRRP-GUI/tests/%1").arg(itemText));

    if(file.open(QIODevice::ReadOnly)){
        int lineIndex = 0;
        QTextStream in(&file);

        while(!in.atEnd()){
            QString currentLine = in.readLine();
            QStringList lineToken = currentLine.split(",", Qt::SkipEmptyParts);

            int colIndex = 0;
            for(auto& token : lineToken){
                QStandardItem* item = new QStandardItem(token);
                fileTableModel->setItem(lineIndex, colIndex, item);
                colIndex++;
            }
            lineIndex++;
        }
        file.close();
    }
    ui->tableView->setModel(fileTableModel);
}

void MainWindow::MainWindow::handleButton(){
    ui->generalFrame->setVisible(!ui->generalFrame->isVisible());
}
