#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <qfilesystemwatcher.h>
#include <QFile>

class GeneralWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralWindow(QWidget* parent = nullptr);
    ~GeneralWindow();

public slots:
    void readFile(const QString& file);

private:
    QStandardItemModel* fileTableModel;
    QTableView* tableView;
    QFileSystemWatcher* fileWatcher;
};

#endif // GENERALWINDOW_H
