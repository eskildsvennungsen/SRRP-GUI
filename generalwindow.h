#ifndef GENERALWINDOW_H
#define GENERALWINDOW_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>
#include <qfilesystemwatcher.h>
#include <QFile>
#include <QProgressBar>
#include <QVBoxLayout>

/*!
* @brief Represents the general window.
*/

class GeneralWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GeneralWindow(QWidget* parent = nullptr);
    ~GeneralWindow();

public slots:
    /*!
    * @brief Reads file to be displayed.
    * @param file Relative path to file.
    */
    void readFile(QString file);

private:
    QStandardItemModel* fileTableModel;
    QTableView* tableView;
    QFileSystemWatcher* fileWatcher;
    QString filepath;
    QProgressBar* progressBar;
    QVBoxLayout* mainLayout;

};

#endif // GENERALWINDOW_H
