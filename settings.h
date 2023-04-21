#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>


class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();


private slots:
    void activate();

private:
    QListWidget* m_list;
    QTableWidget* m_table;
    QList<QPushButton*> buttons;
};

#endif // SETTINGS_H
