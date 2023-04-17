
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardItemModel>

enum class BagSizes{
    SMALL = 1,
    MEDIUM = 2,
    LARGE = 3,
    XLARGE = 4
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readFile();

private slots:
    void onBagSizeChange();
    void newDataStream();
    void handleButton();
    void test();

private:
    Ui::MainWindow *ui;
    QString currentFile;
    QStandardItemModel* model;
};

#endif // MAINWINDOW_H
