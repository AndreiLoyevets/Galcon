/// @author Kulykivsky Vitaliy
#ifndef USERNAMEVALIDATOR_H
#define USERNAMEVALIDATOR_H

#include <QValidator>

class CUserNameValidator : public QValidator
{
public:
    CUserNameValidator(QObject* pobj = 0);
    virtual State validate(QString &, int &) const;
};

#endif // USERNAMEVALIDATOR_H
