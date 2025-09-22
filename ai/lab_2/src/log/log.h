#pragma ocne

#ifndef LOG_H
#define LOG_H

// #define WITH_LOG

#include <string>
#include <QString>

template <typename... Args>
void Log(                   const                   char*           str, Args... args);
void Log(                   const                   char*           str);
void Log(                   const                   std::string&    str);
void Log(                   const                   QString&        str);

void LogWithWarning(        const                   QString&        str);
void LogWithError(          const                   QString&        str);
void LogWithInformation(    const                   QString&        str);

#endif // LOG_H