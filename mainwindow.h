
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardItemModel>
#include <QFileSystemModel>

#include "settings.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleButton();
    void readFile(QModelIndex index);
    void activateHistory();

private:
    Ui::MainWindow* ui;
    QStandardItemModel* fileTableModel;
    QFileSystemModel* fileListModel;
private:
    void clearFrame();
};

#endif // MAINWINDOW_H
