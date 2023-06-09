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
#include <QButtonGroup>
#include <QFormLayout>



/*!
 * @brief Stores relevant information about bagtype
 */
struct BagInfo{
    explicit BagInfo(QString n, int w, int h) : name(n), width(w), height(h) {}
    QString name;
    int width;
    int height;
};

/*!
 * @brief System settings
 *
 * Lets the user controll the linear actuators to raise/lower the system based on bag type.
*/
class SettingsWindow : public QWidget
{
    Q_OBJECT
public:
    explicit SettingsWindow(QWidget *parent = nullptr);
    ~SettingsWindow();
    QFormLayout* globalSettingsForm(QJsonObject, QString);
    void modifyJsonValue(QJsonValue& destValue, const QString& path, const QJsonValue& newValue);
    void modifyJsonValue(QJsonDocument& doc, const QString& path, const QJsonValue& newValue);
public slots:
    /*!
     * @brief Reads from json file and displays buttons
     * @param path inputs json file name
     * @return Returns 0 if no file is found, otherwise 1
    */
    bool readBagInfo(const QString& path = "");

    /*!
     * @brief Detects which button is pressed, and sends signal to GPIO on
     * raspberryPi
     *
     * @param index of pressed button
    */
    void buttonPressed(int index);

    /*!
     * @brief Updates JSON file with new width/heigth
    */ 
    virtual void updateBagInfo();

    void updateGlobals();
    void updateRPM();

private:
    BagInfo getBag(const QString& name);

private:
    QButtonGroup* buttons;
    QList<BagInfo> bags;
    QFileSystemWatcher* fileWatcher;
    QHBoxLayout* mainLayout;
};

#endif // SETTINGS_H
