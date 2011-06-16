#include "AddressValidator.h"

CAddressValidator::CAddressValidator(QObject *parent) :
    QValidator(parent)
{
}

QValidator::State CAddressValidator::validate(QString &i_str, int &pos) const
{
    // read number
    for(int i = 0; i < i_str.size(); ++i)
    {
        QString strNum;
        while(i_str[i].isDigit())
        {
            strNum += i_str[i];
            ++i;
        }
        if(strNum.toInt() > 256) return Invalid;
    }
    return Acceptable;
}
