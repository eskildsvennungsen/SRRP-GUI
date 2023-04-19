#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QListWidget>


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
    QWidget* parent;
};

#endif // SETTINGS_H
