#include "settings.h"
#include "qobjectdefs.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , fileWatcher(new QFileSystemWatcher(this))
    , mainLayout(new QHBoxLayout(this))
{
    mainLayout->setContentsMargins(0,0,0,0);
    readBagInfo("baginfo.json");
    fileWatcher->addPath(QString("baginfo.json"));

    QObject::connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(readBagInfo(QString)));
}

SettingsWindow::~SettingsWindow(){
    for(auto& button : buttons){
        delete button;
    }
    delete fileWatcher;
    delete mainLayout;
}

void SettingsWindow::readBagInfo(const QString& path){
    QFile inFile(path);

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

    if(!buttons.isEmpty()){
        for(auto& button : buttons){
            delete button;
        }
        bags.clear();
    }

    foreach(const QJsonValue& val, ptsArray){
        QString name = val.toObject().value("name").toString();
        int width = val.toObject().value("width").toInt();
        int heigth = val.toObject().value("height").toInt();
        bags.append(BagInfo(name, width, heigth));
    }

    for(const auto &bag : bags){
        QPushButton* tmp = new QPushButton(QString(bag.name), this);
        tmp->setObjectName(bag.name);
        tmp->setMaximumSize(QSize(150,50));
        buttons.push_back(tmp);
        mainLayout->addWidget(tmp);
    }
}
