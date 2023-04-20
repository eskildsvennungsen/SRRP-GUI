#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTableWidget>


class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

signals:


private slots:
    void activate();

private:
    QListWidget* m_list;
    QTableWidget* m_table;
};

#endif // SETTINGS_H
