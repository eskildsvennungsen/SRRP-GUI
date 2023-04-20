#include "settings.h"
#include <QDebug>

SettingsWindow::SettingsWindow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    m_list = new QListWidget(this);
    m_list->setMinimumHeight(this->height());
    m_list->setMinimumWidth(this->width() / 2);

    m_table = new QTableWidget(50, 6, this);
    m_table->setMinimumHeight(this->height());
    m_table->setMinimumWidth(this->width() / 2);

    layout->addWidget(m_list);
    layout->addWidget(m_table);

    for(int i = 0; i < 100; i++){
        new QListWidgetItem(tr("Item #%1").arg(i+1), m_list);
    }
}

SettingsWindow::~SettingsWindow(){
    delete m_list;
}

void SettingsWindow::SettingsWindow::activate(){
    this->setVisible(!this->isVisible());
    qDebug() << "Nice";
    activateWindow();
}
