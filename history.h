#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QFrame>
#include <QHBoxLayout>
#include <QTableView>
#include <QListView>
#include <QProgressBar>
#include <QVBoxLayout>

/*!
 * @brief History related features
 *
 * A class for displaying the history of the system.
 * Logged data is saved as csv files and can then be retrieved at any time.
*/
class HistoryWindow : public QWidget
{
    Q_OBJECT
public:

    /*!
     *  @brief Initializes all attributes and windows in object.
     *  @param *parent is used to make this object a child of mainwindow
    */
    explicit HistoryWindow(QWidget *parent = nullptr);

    /*!
     *  @brief Deletes all rawpointers
    */
    ~HistoryWindow();

public slots:
    /*!
     *  @brief Reads csv files and dislpays it in fileTableModel
     *  @param index is used for retrieving file name
     */
    void readFile(QModelIndex index);

public:
    QStandardItemModel* fileTableModel;
    QFileSystemModel* fileListModel;
    QHBoxLayout* horizontalLayout;
    QVBoxLayout* verticalLayout;
    QListView* fileList;
    QTableView* tableView;
    QProgressBar* progressBar;

};

#endif // HISTORY_H
