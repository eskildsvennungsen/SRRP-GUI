#include "generalwindow.h"
#include "qheaderview.h"

GeneralWindow::GeneralWindow(QWidget* parent)
    : QWidget(parent),
    fileTableModel(new QStandardItemModel),
    tableView(new QTableView(this)),
    fileWatcher(new QFileSystemWatcher),
    filepath("tests/test0.csv"),
    progressBar(new QProgressBar),
    mainLayout(new QVBoxLayout(this))
{
    fileWatcher->addPath(filepath);

    tableView->setObjectName("tableView");
    tableView->setMinimumSize(parent->size() - QSize(0,50));
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    readFile(QString(filepath));

    QPalette p = palette();
    p.setColor(QPalette::Highlight, Qt::green);
    p.setColor(QPalette::Base, Qt::darkRed);
    progressBar->setPalette(p);

    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(tableView);
    mainLayout->addSpacing(5);
    mainLayout->addWidget(progressBar);

    QObject::connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(readFile(QString)));
}

GeneralWindow::~GeneralWindow(){
    delete fileTableModel;
    delete tableView;
    delete fileWatcher;
    delete progressBar;
}

void GeneralWindow::readFile(QString fileChanged){
    delete fileTableModel;
    fileTableModel = new QStandardItemModel;

    QFile file(fileChanged);

    if(file.open(QIODevice::ReadOnly)){
        int lineIndex = 0;
        int faultyBags = 0;
        QTextStream in(&file);

        while(!in.atEnd()){
            QString currentLine = in.readLine();
            QStringList lineToken = currentLine.split(",", Qt::SkipEmptyParts);

            int colIndex = 0;
            for(auto& token : lineToken){

                QStandardItem* item = new QStandardItem(token);
                item->setTextAlignment(Qt::AlignCenter);
                if(colIndex == 3){
                    if(token == '0'){
                        item->setBackground(QBrush(QColor(Qt::darkGreen), Qt::SolidPattern));
                    } else if(token != "Reason"){
                        item->setBackground(QBrush(QColor(Qt::red), Qt::SolidPattern));
                        item->setForeground(QBrush(Qt::white));
                        faultyBags++;
                    }
                }
                if(lineIndex == 0){
                    fileTableModel->setHorizontalHeaderItem(colIndex, item);
                } else {
                    fileTableModel->setItem(lineIndex, colIndex, item);
                }
                colIndex++;
            }
            lineIndex++;
        }
        file.close();
        progressBar->setMaximum(lineIndex - 1);
        progressBar->setValue(lineIndex - 1 - faultyBags);
    }

    /*Setting horizontal headers creates blank row, this removes it*/
    fileTableModel->removeRow(0);
    tableView->setModel(fileTableModel);
}
