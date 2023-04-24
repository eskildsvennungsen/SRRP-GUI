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
#include <QFileSystemWatcher>

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
    void readBagInfo(const QString& path = "");

private:
    QList<QPushButton*> buttons;
    QList<BagInfo> bags;
    QFileSystemWatcher* fileWatcher;
    QHBoxLayout* mainLayout;
};

#endif // SETTINGS_H
