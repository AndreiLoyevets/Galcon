#include "log.h"

using namespace LogDecl;

CLog::CLog(const QString &i_str) : m_file(i_str)
{
    m_file.open(QIODevice::WriteOnly | QIODevice::Text);
    m_streamOut.setDevice(&m_file);
    m_streamOut.setCodec("Utf8");
}

void CLog::AddToLog(const QString &i_str)
{
    m_streamOut << QTime::currentTime().toString("hh:mm:ss:zzz");
    m_streamOut << "\t" << i_str << "\n";
    m_streamOut.flush();
}

CLog::~CLog()
{
    m_file.close();
}
