#include "UserNameValidator.h"

CUserNameValidator::CUserNameValidator(QObject* pobj)
{
}

QValidator::State CUserNameValidator::validate(QString &str, int &pos) const
{
    QRegExp rex("#");
    if(str.contains(rex))
    {
        return Invalid;
    }
    return Acceptable;
}
