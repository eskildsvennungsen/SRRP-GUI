#include "generalwindow.h"
#include "qheaderview.h"

GeneralWindow::GeneralWindow(QWidget* parent)
    : QWidget(parent),
    fileTableModel(new QStandardItemModel(this)),
    tableView(new QTableView(this)),
    fileWatcher(new QFileSystemWatcher(this))
{
    fileWatcher->addPath("tests/Settings_bagtest.csv");

    tableView = new QTableView(this);
    tableView->setObjectName("tableView");
    tableView->setMinimumSize(parent->size());
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    readFile(QString("tests/Settings_bagtest.csv"));

    QObject::connect(fileWatcher, SIGNAL(fileChanged(const QString &)), this, SLOT(readFile(const QString &)));
}

GeneralWindow::~GeneralWindow(){
    delete fileTableModel;
    delete tableView;
    delete fileWatcher;
}

void GeneralWindow::readFile(const QString& fileChanged){
    delete fileTableModel;
    fileTableModel = new QStandardItemModel;

    QFile file(fileChanged);

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
