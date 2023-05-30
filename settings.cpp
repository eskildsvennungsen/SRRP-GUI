#include "settings.h"
#include "qobjectdefs.h"
#include <QDebug>
#include <QFuture>
#include <stdlib.h>
#include <QIcon>
 #include <QLineEdit>
#include <QDialog>
#include <QLabel>
#include <QDialogButtonBox>
 #include <QToolButton>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include "qapplication.h"


SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , buttons(new QButtonGroup)
    , fileWatcher(new QFileSystemWatcher(this))
    , mainLayout(new QHBoxLayout(this))
{
    mainLayout->setContentsMargins(0,0,0,0);
    readBagInfo("baginfo.json");
    fileWatcher->addPath(QString("baginfo.json"));
    this->setMinimumSize(parent->size() - QSize(0, 10));

    QObject::connect(buttons, SIGNAL(idClicked(int)), this, SLOT(buttonPressed(int)));
    QObject::connect(fileWatcher, SIGNAL(fileChanged(QString)), this, SLOT(readBagInfo(QString)));
}

SettingsWindow::~SettingsWindow(){
    delete buttons;
    delete fileWatcher;
    delete mainLayout;
}


bool SettingsWindow::readBagInfo(const QString& path){
    if(!mainLayout->isEmpty()){
        qDeleteAll(buttons->buttons());
        qDeleteAll(mainLayout->children());
        bags.clear();
    }

    QPushButton* custom = new QPushButton(QIcon(tr("%1/res/settings_white_24dp.svg").arg(qApp->applicationDirPath())), "", this);
    custom->setIconSize(QSize(25, 25));
    custom->setObjectName("Settings");
    custom->setMaximumSize(50,50);
    buttons->addButton(custom);

    QFile inFile(path);

    inFile.open(QIODevice::ReadOnly|QIODevice::Text);
    QByteArray data = inFile.readAll();
    inFile.close();

    QJsonParseError errorPtr;
    QJsonDocument doc = QJsonDocument::fromJson(data, &errorPtr);
    if (doc.isNull()) {
        qDebug() << errorPtr.errorString();
        return 0;
    }

    QVBoxLayout* v_layout = new QVBoxLayout();
    QHBoxLayout* h_layout = new QHBoxLayout();
    QHBoxLayout* form_layout = new QHBoxLayout();

    h_layout->addWidget(custom);

    QJsonObject rootObj = doc.object();
    QJsonObject globalSettings = rootObj.value("Global").toObject();
    QFormLayout* form = globalSettingsForm(globalSettings, QString("mod1"));
    QFormLayout* form2 = globalSettingsForm(globalSettings, QString("mod2"));
    QFormLayout* form3 = globalSettingsForm(globalSettings, QString("mod3"));
    form_layout->addLayout(form);
    form_layout->addLayout(form2);
    form_layout->addLayout(form3);

    for(const QJsonValue& val : rootObj){
        if(val.toObject() == globalSettings) continue;
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
        h_layout->addWidget(tmp);
    }

    v_layout->addLayout(h_layout);
    v_layout->addSpacing(10);
    v_layout->addLayout(form_layout);
    v_layout->setAlignment(Qt::AlignCenter);
    mainLayout->addLayout(v_layout);
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

void SettingsWindow::updateGlobals(){
    QFile file("baginfo.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QJsonParseError JsonParseError;
    QList<QLineEdit *> widgets = this->parent()->findChildren<QLineEdit *>();
    QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromStdString(file.readAll().toStdString()));
    file.close();
    foreach(auto *w, widgets) {
        if(w->objectName().contains(this->sender()->objectName())){
            modifyJsonValue(doc, tr("Global.%1.%2").arg(this->sender()->objectName()).arg(w->objectName().remove(this->sender()->objectName())), w->text().toInt());
        }
    }
    file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
    file.write(doc.toJson());
    file.close();
}

QFormLayout* SettingsWindow::globalSettingsForm(QJsonObject inputObject, QString module){
    QList<QLabel *> label_for_deletion = this->findChildren<QLabel *>();
    QList<QLineEdit *> lineedit_for_deletiong = this->parent()->findChildren<QLineEdit *>();
    foreach(auto& x, lineedit_for_deletiong){
        delete x;
    }
    foreach(auto& x, label_for_deletion){
        delete x;
    }
    if(this->findChild<QPushButton*>(QString(module))){
        delete this->findChild<QPushButton*>(QString(module));
    }

    QFormLayout* form = new QFormLayout();
    QJsonObject globalSettings = inputObject.value(module).toObject();

    for(auto i = globalSettings.begin(); i != globalSettings.end(); i++){
        QLineEdit* tmp = new QLineEdit(tr("%1").arg(i.value().toInt()));
        tmp->setObjectName(QString("%1%2").arg(i.key()).arg(module));
        tmp->setMaximumWidth(200);
        QLabel* label = new QLabel(tr("%1").arg(i.key()));
        form->addRow(label, tmp);
    }
    form->setFormAlignment(Qt::AlignHCenter);

    QPushButton* button = new QPushButton(QString("Update %1").arg(module));
    button->setObjectName(module);
    button->setMaximumWidth(200);

    QObject::connect(button, SIGNAL(clicked()), this, SLOT(updateGlobals()));

    form->addWidget(button);

    return form;
}

void SettingsWindow::modifyJsonValue(QJsonValue& destValue, const QString& path, const QJsonValue& newValue)
{
    const int indexOfDot = path.indexOf('.');
    const QString dotPropertyName = path.left(indexOfDot);
    const QString dotSubPath = indexOfDot > 0 ? path.mid(indexOfDot + 1) : QString();

    const int indexOfSquareBracketOpen = path.indexOf('[');
    const int indexOfSquareBracketClose = path.indexOf(']');

    const int arrayIndex = path.mid(indexOfSquareBracketOpen + 1, indexOfSquareBracketClose - indexOfSquareBracketOpen - 1).toInt();

    const QString squareBracketPropertyName = path.left(indexOfSquareBracketOpen);
    const QString squareBracketSubPath = indexOfSquareBracketClose > 0 ? (path.mid(indexOfSquareBracketClose + 1)[0] == '.' ? path.mid(indexOfSquareBracketClose + 2) : path.mid(indexOfSquareBracketClose + 1)) : QString();

    // determine what is first in path. dot or bracket
    bool useDot = true;
    if (indexOfDot >= 0) // there is a dot in path
    {
        if (indexOfSquareBracketOpen >= 0) // there is squarebracket in path
        {
            if (indexOfDot > indexOfSquareBracketOpen)
                useDot = false;
            else
                useDot = true;
        }
        else
            useDot = true;
    }
    else
    {
        if (indexOfSquareBracketOpen >= 0)
            useDot = false;
        else
            useDot = true; // acutally, id doesn't matter, both dot and square bracket don't exist
    }

    QString usedPropertyName = useDot ? dotPropertyName : squareBracketPropertyName;
    QString usedSubPath = useDot ? dotSubPath : squareBracketSubPath;

    QJsonValue subValue;
    if (destValue.isArray())
        subValue = destValue.toArray()[usedPropertyName.toInt()];
    else if (destValue.isObject())
        subValue = destValue.toObject()[usedPropertyName];
    else
        qDebug() << "oh, what should i do now with the following value?! " << destValue;

    if(usedSubPath.isEmpty())
    {
        subValue = newValue;
    }
    else
    {
        if (subValue.isArray())
        {
            QJsonArray arr = subValue.toArray();
            QJsonValue arrEntry = arr[arrayIndex];
            modifyJsonValue(arrEntry,usedSubPath,newValue);
            arr[arrayIndex] = arrEntry;
            subValue = arr;
        }
        else if (subValue.isObject())
            modifyJsonValue(subValue,usedSubPath,newValue);
        else
            subValue = newValue;
    }

    if (destValue.isArray())
    {
        QJsonArray arr = destValue.toArray();
        arr[arrayIndex] = subValue;
        destValue = arr;
    }
    else if (destValue.isObject())
    {
        QJsonObject obj = destValue.toObject();
        obj[usedPropertyName] = subValue;
        destValue = obj;
    }
    else
        destValue = newValue;
}

void SettingsWindow::modifyJsonValue(QJsonDocument& doc, const QString& path, const QJsonValue& newValue)
{
    QJsonValue val;
    if (doc.isArray())
        val = doc.array();
    else
        val = doc.object();

    modifyJsonValue(val,path,newValue);

    if (val.isArray())
        doc = QJsonDocument(val.toArray());
    else
        doc = QJsonDocument(val.toObject());
}



