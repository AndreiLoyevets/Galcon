/// @author Kulykivsky Vitaliy
#ifndef ADDRESSVALIDATOR_H
#define ADDRESSVALIDATOR_H

#include <QValidator>
#include <QDebug>

class CAddressValidator : public QValidator
{
    Q_OBJECT
public:
    explicit CAddressValidator(QObject *parent = 0);
    virtual State validate(QString &, int &) const;
signals:

public slots:

};

#endif // ADDRESSVALIDATOR_H
