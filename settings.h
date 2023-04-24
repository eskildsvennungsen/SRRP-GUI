#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include <QFile>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonArray>

struct BagInfo{
    BagInfo(QString n, int w, int h) : name(n), width(w), height(h) {}
    QString name;
    int width;
    int height;
};

class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();

private slots:
    void readBagInfo();

private:
    QList<QPushButton*> buttons;
    QList<BagInfo> bags;
};

#endif // SETTINGS_H
