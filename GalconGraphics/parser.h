/// @file parser.h
/// @brief convert server's commands(QString) to CMessage, using protocol
/// @author Kulykivsky Vitaliy
/// @date Created on: 01-Jun-2011

#ifndef PARSER_H
#define PARSER_H

#include <Qt>
#include <QStringList>
#include <QDebug>

#include "message.h"

using namespace MessageDecl;

namespace ParserDecl
{

    class CParser
    {
    public:
        /// @brief default ctor
        CParser();

        /// @brief convert message to string
        /// @param i_msg in, message wich we convert to string
        QString ParseToString(CMessage* i_msg);
        //QString ParseToString(CStepMessage* i_msg);

        /// @brief convert input string message to  CMessage
        /// @param i_str in, convert string to CMessage
        CMessage* ParseToMessage(const QString& i_str);
    };// CPaser

}; // ParserDecl

#endif // PARSER_H
