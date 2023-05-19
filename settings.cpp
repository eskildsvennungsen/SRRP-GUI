#include "settings.h"
#include "qobjectdefs.h"
#include <QDebug>
#include <QFuture>
#include <stdlib.h>
#include <QIcon>
 #include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QFormLayout>
#include <QDialogButtonBox>
#include "qapplication.h"
// #include <L298N>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , buttons(new QButtonGroup)
    , fileWatcher(new QFileSystemWatcher(this))
    , mainLayout(new QHBoxLayout(this))
{
    mainLayout->setContentsMargins(0,0,0,0);
    readBagInfo("baginfo.json");
    fileWatcher->addPath(QString("baginfo.json"));
    this->setMinimumSize(parent->size() - QSize(0,30));

    QObject::connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(readBagInfo(QString)));
    QObject::connect(buttons, SIGNAL(idClicked(int)), this, SLOT(buttonPressed(int)));
}

SettingsWindow::~SettingsWindow(){
    delete buttons;
    delete fileWatcher;
    delete mainLayout;
}


bool SettingsWindow::readBagInfo(const QString& path){
    QPushButton* custom = new QPushButton(QIcon(tr("%1/res/settings_white_24dp.svg").arg(qApp->applicationDirPath())), "", this);
    custom->setIconSize(QSize(25, 25));
    custom->setObjectName("Settings");
    custom->setMaximumSize(50,50);

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

    if(!buttons->buttons().isEmpty()){
        qDeleteAll(buttons->buttons());
        bags.clear();
    }

    for(const QJsonValue& val : rootObj){
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

    mainLayout->addWidget(custom);
    buttons->addButton(custom);
    inFile.close();

    return 1;
}



void SettingsWindow::buttonPressed(int index){
    QString buttonPressed = buttons->button(index)->objectName();

    if(buttonPressed == "Settings"){
        QDialog tmp(this);
        tmp.setMinimumSize(QSize(200, 150));
        QVBoxLayout* v_layout = new QVBoxLayout();
        QFormLayout* layout = new QFormLayout();


        QLineEdit* height = new QLineEdit(tr("%1").arg(getBag(buttonPressed).height));
        height->setObjectName(QString("heightBox"));

        QLineEdit* width = new QLineEdit(tr("%1").arg(getBag(buttonPressed).width));
        width->setObjectName(QString("widthBox"));

        layout->addRow(new QLabel("Height"), height);
        layout->addRow(new QLabel("Width"), width);


        QDialogButtonBox* buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                         | QDialogButtonBox::Cancel);

        QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(updateBagInfo()));
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, &tmp, &QDialog::accept);
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, &tmp, &QDialog::reject);

        v_layout->addLayout(layout);
        v_layout->addWidget(buttonBox);
        tmp.setLayout(v_layout);

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

void SettingsWindow::updateBagInfo(){
    QFile file("baginfo.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();
    QJsonObject RootObject = JsonDocument.object();
    QJsonValueRef ref = RootObject.find("Settings").value();
    QJsonObject m_addvalue = ref.toObject();

    QString new_height = 0;
    QString new_width = 0;
    for(auto& x : this->children()){
        if(!x->findChildren<QLineEdit*>().isEmpty()){
            new_height = x->findChildren<QLineEdit*>().at(0)->text();
            new_width = x->findChildren<QLineEdit*>().at(1)->text();
        }
    }
    m_addvalue.insert("height", new_height.toDouble());
    m_addvalue.insert("width", new_width.toDouble());

    ref=m_addvalue;
    JsonDocument.setObject(RootObject);
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(JsonDocument.toJson());
    file.close();
}





