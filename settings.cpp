#include "settings.h"
#include "qobjectdefs.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    layout->setContentsMargins(0,0,0,0);

    readBagInfo();

    for(auto& bag : bags){
        QPushButton* tmp = new QPushButton(QString(bag.name), this);
        tmp->setObjectName(bag.name);
        tmp->setMaximumSize(QSize(150,50));
        buttons.push_back(tmp);
        layout->addWidget(tmp);
    }
}

SettingsWindow::~SettingsWindow(){
    for(auto& button : buttons){
        delete button;
    }
}

void SettingsWindow::readBagInfo(){
    QFile inFile("baginfo.json");
    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
        qDebug() << errorPtr.errorString();
        return;
    }
    QJsonObject rootObj = doc.object();
    QJsonArray ptsArray = rootObj.value("BagTypes").toArray();
    foreach(const QJsonValue & val, ptsArray){
        QString name = val.toObject().value("name").toString();
        int width = val.toObject().value("width").toInt();
        int heigth = val.toObject().value("height").toInt();
        bags.append(BagInfo(name, width, heigth));
    }
}
