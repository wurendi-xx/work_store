#include <QDebug>
#include "signalsandslots3.h"

SignalsAndSlots3::SignalsAndSlots3(QObject *parent) : QObject(parent)
{
    connect(this, SIGNAL(sigPrint(QString)), this, SLOT(sltPrint(QString)));
    emit sigPrint("Hello");
}

void SignalsAndSlots3::sltPrint(const QString &text)
{
    qDebug() << text;
}
