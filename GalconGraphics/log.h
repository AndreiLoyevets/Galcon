/// @file
/// @brief it uses for write to file all information which we send to server
///        or receive from server
/// @author: Kulykivsky Vitaliy
/// @date: 01-Jun-2011

#ifndef LOG_H
#define LOG_H

#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTime>

namespace LogDecl
{
    /// @class CLog
    /// @brief write text to file all information which we send to server
    ///        or receive from server
    /// @respons
    /// @collab
    class CLog
    {
    public:
        /// @brief default ctor
        CLog(const QString& i_str = "log.txt");

        /// @brief add information to logfile
        void AddToLog(const QString& i_str);

        /// @brief dtor
        ~CLog();

    private:
        QFile m_file; ///< file which contains all log information
        QTextStream m_streamOut; ///< for writting to file
    }; // Clog

}; // LogDecl

#endif // LOG_H
