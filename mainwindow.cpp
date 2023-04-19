
#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , fileTableModel(new QStandardItemModel)
    , fileListModel(new QFileSystemModel)
    , settingsWindow(new SettingsWindow(this))
{
    ui->setupUi(this);
    this->resize(1000, 300);

    //Initiate fileView to display all test files
    QString directory = qApp->applicationDirPath() + "/tests";
    ui->fileList->setModel(fileListModel);
    ui->fileList->setRootIndex(fileListModel->setRootPath(directory));

    //Fits tableView to window width
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(ui->fileList, SIGNAL(clicked(QModelIndex)), this, SLOT(readFile(QModelIndex)));
    QObject::connect(ui->general, SIGNAL(clicked()), this, SLOT(handleButton()));
    QObject::connect(ui->settings, SIGNAL(clicked()), settingsWindow, SLOT(activate()));
}

MainWindow::~MainWindow(){
    delete ui;
    delete fileListModel;
    delete fileTableModel;
}

//Read from csv file and display in tableView
void MainWindow::MainWindow::readFile(QModelIndex index){
    delete fileTableModel;
    fileTableModel = new QStandardItemModel;

    QString itemText = index.data(Qt::DisplayRole).toString();
    QString path = qApp->applicationDirPath();
    QFile file(tr("%1/tests/%2").arg(path, itemText));

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
    ui->generalFrame->setFocusProxy(settingsWindow);
    //ui->generalFrame->setVisible(!ui->generalFrame->isVisible());
}
