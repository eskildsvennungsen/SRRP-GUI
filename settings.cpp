#include "settings.h"
#include <QDebug>
#include <QHBoxLayout>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
    , parent(parent)
{
    this->setVisible(false);
    this->resize(700,300);
    QHBoxLayout* layout = new QHBoxLayout(this);

    m_list = new QListWidget(this);
    m_list->setMinimumHeight(this->height());
    m_list->setMinimumWidth(this->width() / 2);

    layout->addWidget(m_list);

    for(int i = 0; i < 100; i++){
        new QListWidgetItem(tr("Item #%1").arg(i+1), m_list);
    }
}

SettingsWindow::~SettingsWindow(){
    delete parent;
    delete m_list;
}

void SettingsWindow::SettingsWindow::activate(){
    this->setVisible(!this->isVisible());
    QFrame* frame = parent->findChild<QFrame*>("generalFrame");
    this->resize(frame->width(), frame->height());
    qDebug() << "Nice";
    activateWindow();
    raise();
}
