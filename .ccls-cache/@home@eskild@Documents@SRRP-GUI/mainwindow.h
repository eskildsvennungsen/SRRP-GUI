﻿
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardItemModel>
#include <QFileSystemModel>


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
    void activateHistory();
    void activateSettings();

private:
    Ui::MainWindow* ui;

private:
    void clearFrame();
};

#endif // MAINWINDOW_H
