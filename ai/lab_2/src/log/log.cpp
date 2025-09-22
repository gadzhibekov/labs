#include "log.h"

#include <iostream>
#include <cstdio>
#include <QMessageBox>

template <typename... Args>
void Log(const char* str, Args... args)
{
#ifdef WITH_LOG
    printf(str, args...);
#endif // WITH_LOG
}

void Log(const char* str)
{
#ifdef WITH_LOG
    printf("%s\n", str);
#endif // WITH_LOG
}

void Log(const std::string& str)
{
#ifdef WITH_LOG 
    Log(str.c_str());
#endif // WITH_LOG"
}

void Log(const QString& str)
{
#ifdef WITH_LOG 
    Log(str.toStdString());
#endif // WITH_LOG"
}

void LogWithWarning(const QString& str)
{
#ifdef WITH_LOG 
    QMessageBox::warning(nullptr, "Предупрежедение", str);
#endif // WITH_LOG"
}

void LogWithError(const QString& str)
{
#ifdef WITH_LOG 
    QMessageBox::critical(nullptr, "Ошибка", str);
#endif // WITH_LOG"
}

void LogWithInformation(const QString& str)
{
#ifdef WITH_LOG
    QMessageBox::information(nullptr, "Информация", str);
#endif // WITH_LOG"
}