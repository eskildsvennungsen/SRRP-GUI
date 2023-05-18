
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QStandardItemModel>
#include <QFileSystemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


/*!
 * @brief The main window for the whole application
 *
 * This window is designed with a UI file. The purpose of this is to setup the main structure of
 * the application. It's responsible for instansiating the other window respectevly. It's structured
 * such that withing the central widget there is a frame, depening on which buttons the user presses
 * the cooresponding object is created.
*/
class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    /*!
     * @brief Sets up the UI design.
    */
    MainWindow(QWidget *parent = nullptr);
    /*!
     * @brief Deletes ui
    */
    ~MainWindow();

public slots:
    /*!
     * @brief Creates HistoryWindow object and emplaces it in MainWindows generalFrame.
    */
    void activateHistory();
    /*!
     * @brief Creates SettingsWindow object and emplaces it in MainWindows generalFrame.
    */
    void activateSettings();

    /*! @brief Creates GeneralWindow object and emplaces it in MainWindow*/
    void activateGeneral();

    void test();
private:
    Ui::MainWindow* ui;

private:
    void clearFrame();
};

#endif // MAINWINDOW_H
