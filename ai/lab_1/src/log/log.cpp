#include "log.h"

#include <iostream>
#include <QMessageBox>

#ifdef WITH_LOG 

void Log(const std::string& str)
{
    std::cout << str << std::endl;
}

void Log(const QString& str)
{
    Log(str.toStdString());
}

void LogWithWarning(const QString& str)
{
    QMessageBox::warning(nullptr, "Предупрежедение", str);
}

void LogWithError(const QString& str)
{
    QMessageBox::critical(nullptr, "Ошибка", str);
}

void LogWithInformation(const QString& str)
{
    QMessageBox::information(nullptr, "Информация", str);
}

#endif // WITH_LOG"