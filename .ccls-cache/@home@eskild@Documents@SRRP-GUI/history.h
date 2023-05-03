#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QFrame>
#include <QHBoxLayout>
#include <QTableView>
#include <QListView>


class HistoryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryWindow(QWidget *parent = nullptr);
    ~HistoryWindow();

private slots:
    void readFile(QModelIndex index);

public:
    QStandardItemModel* fileTableModel;
    QFileSystemModel* fileListModel;
    QHBoxLayout* horizontalLayout;
    QHBoxLayout* horizontalLayout_2;
    QListView* fileList;
    QTableView* tableView;

};

#endif // HISTORY_H
