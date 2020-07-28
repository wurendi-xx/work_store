#ifndef SIGNALSANDSLOTS3_H
#define SIGNALSANDSLOTS3_H

#include <QCoreApplication>

class SignalsAndSlots3 : public QObject
{
    Q_OBJECT
public:
    explicit SignalsAndSlots3(QObject *parent = 0);

signals:
    void sigPrint(const QString& text);

public slots:
    void sltPrint(const QString& text);
};


#endif // SIGNALSANDSLOTS3_H
