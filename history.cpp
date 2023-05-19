#include "history.h"
#include "qapplication.h"
#include "qheaderview.h"


HistoryWindow::HistoryWindow(QWidget *parent)
    : QWidget{parent}
    , fileTableModel(new QStandardItemModel)
    , fileListModel(new QFileSystemModel)
    , horizontalLayout(new QHBoxLayout(this))
    , verticalLayout(new QVBoxLayout)
    , fileList(new QListView)
    , tableView(new QTableView)
    , progressBar(new QProgressBar)
{
    horizontalLayout->setObjectName("horizontalLayout");
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    fileList->setObjectName("fileList");
    fileList->setViewMode(QListView::ListMode);

    QString directory = qApp->applicationDirPath() + "tests/";
    fileList->setModel(fileListModel);
    fileList->setRootIndex(fileListModel->setRootPath(directory));

    tableView->setObjectName("tableView");
    tableView->setMinimumSize(parent->size() - QSize(150, 0));
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QPalette p = palette();
    p.setColor(QPalette::Mid, Qt::darkGreen);
    progressBar->setPalette(p);

    verticalLayout->addWidget(tableView);
    verticalLayout->addWidget(progressBar);

    horizontalLayout->addWidget(fileList);
    horizontalLayout->addLayout(verticalLayout);

    QObject::connect(fileList, SIGNAL(clicked(QModelIndex)), this, SLOT(readFile(QModelIndex)));
}

HistoryWindow::~HistoryWindow(){
    delete fileTableModel;
    delete fileListModel;
    delete horizontalLayout;
    delete fileList;
    delete tableView;
    delete verticalLayout;
    delete progressBar;
}

void HistoryWindow::readFile(QModelIndex index){
    delete fileTableModel;
    fileTableModel = new QStandardItemModel;

    QString itemText = index.data(Qt::DisplayRole).toString();
    QString path = qApp->applicationDirPath();
    QFile file(tr("%1/tests/%2").arg(path, itemText));

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
                if(colIndex == 3){
                    if(token == '0'){
                        item->setBackground(QBrush(QColor(Qt::darkGreen), Qt::SolidPattern));
                    } else if(token != "Reason"){
                        item->setBackground(QBrush(QColor(Qt::darkRed), Qt::SolidPattern));
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
