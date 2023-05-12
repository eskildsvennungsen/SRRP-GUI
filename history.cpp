#include "history.h"
#include "qapplication.h"
#include "qheaderview.h"


HistoryWindow::HistoryWindow(QWidget *parent)
    : QWidget{parent}
    , fileTableModel(new QStandardItemModel)
    , fileListModel(new QFileSystemModel)
    , horizontalLayout(new QHBoxLayout)
    , horizontalLayout_2(new QHBoxLayout)
    , fileList(new QListView)
    , tableView(new QTableView)
{
    horizontalLayout_2 = new QHBoxLayout(this);
    horizontalLayout_2->setObjectName("horizontalLayout_2");
    horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
    fileList = new QListView(this);
    fileList->setObjectName("fileList");
    fileList->setViewMode(QListView::ListMode);

    QString directory = qApp->applicationDirPath() + "/tests";
    fileList->setModel(fileListModel);
    fileList->setRootIndex(fileListModel->setRootPath(directory));

    horizontalLayout_2->addWidget(fileList);

    tableView = new QTableView(this);
    tableView->setObjectName("tableView");
    tableView->setMinimumSize(QSize(700, 0));

    horizontalLayout_2->addWidget(tableView);

    horizontalLayout->addWidget(this);

    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QObject::connect(fileList, SIGNAL(clicked(QModelIndex)), this, SLOT(readFile(QModelIndex)));
}

HistoryWindow::~HistoryWindow(){
    delete fileTableModel;
    delete fileListModel;
    delete horizontalLayout;
    delete horizontalLayout_2;
    delete fileList;
    delete tableView;
}

void HistoryWindow::readFile(QModelIndex index){
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
    tableView->setModel(fileTableModel);
}
