#include "settings.h"
#include "qobjectdefs.h"
#include <QDebug>
#include <QFuture>
#include <QtConcurrent>
#include <stdlib.h>
#include <QIcon>
 #include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , fileWatcher(new QFileSystemWatcher(this))
    , mainLayout(new QHBoxLayout(this))
    , buttons(new QButtonGroup)
{
    mainLayout->setContentsMargins(0,0,0,0);
    readBagInfo("baginfo.json");
    fileWatcher->addPath(QString("baginfo.json"));

    QObject::connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(readBagInfo(QString)));
    QObject::connect(buttons, SIGNAL(idClicked(int)), this, SLOT(buttonPressed(int)));

    QPushButton* custom = new QPushButton(QIcon("res/40031.png"), "", this);
    custom->setIconSize(QSize(15, 15));
    custom->setObjectName("Settings");
    custom->setMaximumSize(50,50);
    mainLayout->addWidget(custom);
    buttons->addButton(custom);
}

SettingsWindow::~SettingsWindow(){
    delete buttons;
    delete fileWatcher;
    delete mainLayout;
}

bool SettingsWindow::readBagInfo(const QString& path){
    QFile inFile(path);

    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << "Parse failed";
        qDebug() << errorPtr.errorString();
        return 0;
    }

    QJsonObject rootObj = doc.object();
    QJsonArray bagArray = rootObj.value("BagTypes").toArray();

    if(!buttons->buttons().isEmpty()){
        qDeleteAll(buttons->buttons());
        bags.clear();
    }

    for(const QJsonValue& val : bagArray){
        QString name = val.toObject().value("name").toString();
        int width = val.toObject().value("width").toInt();
        int heigth = val.toObject().value("height").toInt();
        bags.append(BagInfo(name, width, heigth));
    }

    for(const auto &bag : bags){
        if(bag.name == "Settings") continue;
        QPushButton* tmp = new QPushButton(bag.name, this);
        tmp->setObjectName(bag.name);
        tmp->setToolTip(QString("Width: %1\nHeigth: %2").arg(bag.width).arg(bag.height));
        tmp->setMaximumSize(QSize(150,50));
        buttons->addButton(tmp);
        mainLayout->addWidget(tmp);
    }

    inFile.close();
    return 1;
}



void SettingsWindow::buttonPressed(int index){
    QString buttonPressed = buttons->button(index)->objectName();
    qDebug() << buttonPressed;

    if(buttonPressed == "Settings"){
        QDialog tmp(this);
        tmp.setMinimumSize(QSize(200, 150));
        QVBoxLayout* mainLayout = new QVBoxLayout();
        QFormLayout* layout = new QFormLayout();

        layout->addRow(new QLabel("Height"), new QLineEdit(tr("%1").arg(getBag(buttonPressed).height)));
        layout->addRow(new QLabel("Width"), new QLineEdit(tr("%1").arg(getBag(buttonPressed).width)));

        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);

        QObject::connect(buttonBox, &QDialogButtonBox::accepted, &tmp, &QDialog::accept);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, &tmp, &QDialog::reject);

        mainLayout->addLayout(layout);
        mainLayout->addWidget(buttonBox);
        tmp.setLayout(mainLayout);

        tmp.exec();
    }

    /* auto task = QtConcurrent::task([]{ system("python ac.py"); }).spawn(); Leave it be if we ever need tasking */
}

BagInfo SettingsWindow::getBag(const QString& name){
    for(auto& bag : bags){
        if(bag.name == name) return bag;
    }
    return BagInfo("", 0, 0);
}





